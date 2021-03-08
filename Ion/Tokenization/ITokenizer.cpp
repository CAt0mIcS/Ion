#include "Ipch.h"
#include "ITokenizer.h"
#include "Core/ICompiler.h"


namespace At0::Ion
{
	Position::Position(uint32_t idx, int line, int col) : index(idx), line(line), column(col) {}

	void Position::Advance(char currentChar)
	{
		++index;
		++column;

		if (currentChar == '\n')
		{
			++line;
			column = 0;
		}
	}

	std::ostream& operator<<(std::ostream& os, const Tokenizer::Token& token)
	{
		std::string tokenStr = "Unknown Token " + std::to_string((uint32_t)token.GetType());
		switch (token.GetType())
		{
		case Tokenizer::TokenType::Int: tokenStr = "Int " + *(int*)token.GetData().data(); break;
		case Tokenizer::TokenType::UInt:
			tokenStr = "UInt " + std::to_string(*(uint32_t*)token.GetData().data());
			break;
		case Tokenizer::TokenType::Float:
			tokenStr = "Float " + std::to_string(*(float*)token.GetData().data());
			break;
		case Tokenizer::TokenType::Double: tokenStr = "Double"; break;
		case Tokenizer::TokenType::Plus: tokenStr = "Plus"; break;
		case Tokenizer::TokenType::Minus: tokenStr = "Minus"; break;
		case Tokenizer::TokenType::Multiply: tokenStr = "Multiply"; break;
		case Tokenizer::TokenType::Divide: tokenStr = "Divide"; break;
		case Tokenizer::TokenType::LeftParentheses: tokenStr = "LeftParentheses"; break;
		case Tokenizer::TokenType::RightParentheses: tokenStr = "RightParentheses"; break;
		case Tokenizer::TokenType::Equal: tokenStr = "Equal"; break;
		case Tokenizer::TokenType::Identifier:
			tokenStr = "Identifier " + std::string(token.GetData().begin(), token.GetData().end());
			break;
		case Tokenizer::TokenType::Keyword:
			tokenStr = "Keyword " + std::string(token.GetData().begin(), token.GetData().end());
			break;
		case Tokenizer::TokenType::Function: tokenStr = "Function"; break;
		case Tokenizer::TokenType::EndOfFile: tokenStr = "EndOfFile"; break;
		case Tokenizer::TokenType::Colon: tokenStr = "Colom"; break;
		case Tokenizer::TokenType::SystemSemantic:
			tokenStr =
				"SystemSemantic " + std::string(token.GetData().begin(), token.GetData().end());
			break;
		case Tokenizer::TokenType::Dot: tokenStr = "Dot"; break;
		case Tokenizer::TokenType::OpenScope: tokenStr = "Open Scope"; break;
		case Tokenizer::TokenType::CloseScope: tokenStr = "Close Scope"; break;
		case Tokenizer::TokenType::EndOfLine: tokenStr = "EndOfLine"; break;
		case Tokenizer::TokenType::Assignment: tokenStr = "Assignment"; break;
		case Tokenizer::TokenType::Comma: tokenStr = "Comma"; break;
		}

		os << "TokenType: " << tokenStr;
		return os;
	}

	Tokenizer::Tokenizer(std::string fileContent, Compiler& compiler)
		: m_Compiler(compiler), m_Text(std::move(fileContent)), m_Position(-1, 1, -1)
	{
		Advance();
		Start();
	}

	void Tokenizer::Advance()
	{
		m_Position.Advance(m_CurrentChar);
		if (m_Position.index < m_Text.size())
			m_CurrentChar = m_Text[m_Position.index];
		else
			m_CurrentChar = '\0';
	}

	void Tokenizer::Start()
	{
		std::vector<Tokenizer::Token> tokens;

		while (m_CurrentChar != '\0')
		{
			SkipUnknown();

			// Get numbers
			if (auto it = std::find(s_Numbers.begin(), s_Numbers.end(), m_CurrentChar);
				it != s_Numbers.end())
			{
				tokens.emplace_back(MakeNumber());
			}
			// Get identifiers
			else if (auto it = std::find(s_Letters.begin(), s_Letters.end(), m_CurrentChar);
					 it != s_Letters.end())
			{
				tokens.emplace_back(MakeIdentifier());
			}
			else if (m_CurrentChar == '+')
			{
				tokens.emplace_back(TokenType::Plus, 0, m_Position);
				Advance();
			}
			else if (m_CurrentChar == '-')
			{
				tokens.emplace_back(TokenType::Minus, 0, m_Position);
			}
			else if (m_CurrentChar == '*')
			{
				tokens.emplace_back(TokenType::Multiply, 0, m_Position);
				Advance();
			}
			else if (m_CurrentChar == '/')
			{
				tokens.emplace_back(TokenType::Divide, 0, m_Position);
				Advance();
			}
			else if (m_CurrentChar == '(')
			{
				tokens.emplace_back(TokenType::LeftParentheses, 0, m_Position);
				Advance();
			}
			else if (m_CurrentChar == ')')
			{
				tokens.emplace_back(TokenType::RightParentheses, 0, m_Position);
				Advance();
			}
			else if (m_CurrentChar == '!')
			{
				tokens.emplace_back(MakeNotEquals());
			}
			else if (m_CurrentChar == '=')
			{
				tokens.emplace_back(MakeEquals());
			}
			else if (m_CurrentChar == '<')
			{
				tokens.emplace_back(MakeLessThan());
			}
			else if (m_CurrentChar == '>')
			{
				tokens.emplace_back(MakeGreaterThan());
			}
			else if (m_CurrentChar == ',')
			{
				tokens.emplace_back(TokenType::Comma, 0, m_Position);
				Advance();
			}
			else if (m_CurrentChar == '{')
			{
				tokens.emplace_back(TokenType::OpenScope, 0, m_Position);
				Advance();
			}
			else if (m_CurrentChar == '}')
			{
				tokens.emplace_back(TokenType::CloseScope, 0, m_Position);
				Advance();
			}
			else if (m_CurrentChar == ':')
			{
				tokens.emplace_back(TokenType::Colon, 0, m_Position);
				Advance();
			}
			else if (m_CurrentChar == ';')
			{
				tokens.emplace_back(TokenType::EndOfLine, 0, m_Position);
				Advance();
			}
			else if (m_CurrentChar == '.')
			{
				tokens.emplace_back(TokenType::Dot, 0, m_Position);
				Advance();
			}
			else
			{
				if (m_CurrentChar != '\0')
				{
					char ch = m_CurrentChar;
					Advance();
					std::ostringstream errMsg;
					errMsg << "Unexpected character '" << ch << "'";
					m_Compiler.LogError(
						MakeScope<TokenizationError>("TestFile", m_Position.line, errMsg.str()));
				}
			}
		}

		for (Token& tok : tokens)
		{
			std::cout << tok << '\n';
		}
	}

	void Tokenizer::SkipUnknown()
	{
		// Comments
		int startLine = m_Position.line;
		if (m_CurrentChar == '/' && (NextChar() == '/' || PreviousChar() == '/'))
		{
			while (startLine == m_Position.line)
				Advance();
		}

		while (m_CurrentChar == ' ' || m_CurrentChar == '\t' || m_CurrentChar == '\n' ||
			   m_CurrentChar == '\r')
			Advance();
	}

	char Tokenizer::NextChar()
	{
		if (m_Position.index + 1 < m_Text.size())
			return m_Text[m_Position.index + 1];
		return '\0';
	}

	char Tokenizer::PreviousChar()
	{
		if ((int)m_Position.index - 1 >= 0)
			return m_Text[m_Position.index - 1];
		return '\0';
	}

	Tokenizer::Token Tokenizer::MakeNumber()
	{
		std::string numStr = "";
		uint8_t dotCount = 0;
		Position startPos = m_Position;

		auto it = std::find(s_Numbers.begin(), s_Numbers.end(), m_CurrentChar);
		while (m_CurrentChar != '\0' && it != s_Numbers.end() || m_CurrentChar == '.')
		{
			if (m_CurrentChar == '.')
				++dotCount;

			numStr += m_CurrentChar;
			Advance();

			it = std::find(s_Numbers.begin(), s_Numbers.end(), m_CurrentChar);
		}

		if (dotCount == 0)
		{
			// ION_TODO: Determine if uint/int
			return { TokenType::Int, stoi(numStr), startPos, m_Position };
		}
		else if (dotCount == 1)
		{
			if (m_CurrentChar == 'f')
			{
				Advance();
				return { TokenType::Float, stof(numStr), startPos, m_Position };
			}
			else
				return { TokenType::Double, stod(numStr), startPos, m_Position };
		}
		else
		{
			m_Compiler.LogError(MakeScope<TokenizationError>(
				"TestFile", (uint32_t)m_Position.line, "Too many dots in number expression."));
			return { TokenType::EndOfFile, 0 };
		}
	}

	Tokenizer::Token Tokenizer::MakeIdentifier()
	{
		std::string idStr = "";
		Position startPos = m_Position;

		auto itLetter = std::find(s_Letters.begin(), s_Letters.end(), m_CurrentChar);
		auto itNum = std::find(s_Numbers.begin(), s_Numbers.end(), m_CurrentChar);
		while (m_CurrentChar != '\0' && itLetter != s_Letters.end() || itNum != s_Numbers.end())
		{
			idStr += m_CurrentChar;
			Advance();

			itLetter = std::find(s_Letters.begin(), s_Letters.end(), m_CurrentChar);
			itNum = std::find(s_Numbers.begin(), s_Numbers.end(), m_CurrentChar);
		}

		TokenType type = TokenType::Identifier;

		// Identifier is actually a keyword
		if (auto it = std::find(s_Keywords.begin(), s_Keywords.end(), idStr);
			it != s_Keywords.end())
		{
			type = TokenType::Keyword;
		}

		// Identifier is a predefined semantic
		if (auto it = std::find(s_SystemSemantics.begin(), s_SystemSemantics.end(), idStr);
			it != s_SystemSemantics.end())
		{
			type = TokenType::SystemSemantic;
		}

		return { type, idStr, startPos, m_Position };
	}

	Tokenizer::Token Tokenizer::MakeNotEquals()
	{
		Position startPos = m_Position;
		Advance();

		if (m_CurrentChar == '=')
		{
			Advance();
			return Token(TokenType::NotEqual, 0, startPos, m_Position);
		}

		Advance();
		m_Compiler.LogError(
			MakeScope<TokenizationError>("TestFile", m_Position.line, "Expected '=' (after '!')"));
		return { TokenType::NotEqual, 0 };
	}

	Tokenizer::Token Tokenizer::MakeEquals()
	{
		TokenType type = TokenType::Assignment;
		Position startPos = m_Position;
		Advance();

		if (m_CurrentChar == '=')
		{
			Advance();
			type = TokenType::Equal;
		}

		return { type, 0, startPos, m_Position };
	}

	Tokenizer::Token Tokenizer::MakeLessThan()
	{
		TokenType tokenType = TokenType::Less;
		Position startPos = m_Position;
		Advance();

		if (m_CurrentChar == '=')
		{
			Advance();
			tokenType = TokenType::LessEqual;
		}

		return { tokenType, 0, startPos, m_Position };
	}

	Tokenizer::Token Tokenizer::MakeGreaterThan()
	{
		TokenType tokenType = TokenType::Greater;
		Position startPos = m_Position;
		Advance();

		if (m_CurrentChar == '=')
		{
			Advance();
			tokenType = TokenType::GreaterEqual;
		}

		return { tokenType, 0, startPos, m_Position };
	}
}  // namespace At0::Ion
