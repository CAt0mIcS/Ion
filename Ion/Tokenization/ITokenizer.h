#pragma once

#include "../IBase.h"
#include "../Utils/IError.h"

#include <functional>
#include <string.h>
#include <optional>


namespace At0::Ion
{
	struct ION_EXPORT Position
	{
	public:
		Position(uint32_t idx, int line, int col);

		void Advance(char currentChar = '\0');

		uint32_t index;
		int line;
		int column;
	};

	class Compiler;
	class ION_EXPORT Tokenizer
	{
	public:
		enum class TokenType
		{
			Int,
			UInt,
			Float,
			Double,

			Plus,
			Minus,
			Multiply,
			Divide,
			LeftParentheses,
			RightParentheses,
			Assignment,
			Equal,
			NotEqual,
			Less,
			Greater,
			LessEqual,
			GreaterEqual,

			Identifier,
			Keyword,

			Function,
			Comma,
			Colon,
			SystemSemantic,
			Dot,

			OpenScope,
			CloseScope,

			EndOfFile,
			EndOfLine,
		};

		class Token
		{
		public:
			template<typename T>
			Token(TokenType type, T&& data, std::optional<Position> startPos = std::nullopt,
				std::optional<Position> endPos = std::nullopt)
				: m_Type(type)
			{
				m_Data.resize(sizeof(data));
				memcpy(m_Data.data(), &data, sizeof(data));

				if (startPos)
				{
					m_StartPos = startPos;
					m_EndPos = startPos;
					m_EndPos->Advance();
				}
			}

			Token(TokenType type, const std::string& data,
				std::optional<Position> startPos = std::nullopt,
				std::optional<Position> endPos = std::nullopt)
				: m_Type(type)
			{
				m_Data.resize(data.size());
				m_Data = std::vector<char>(data.begin(), data.end());

				if (startPos)
				{
					m_StartPos = startPos;
					m_EndPos = startPos;
					m_EndPos->Advance();
				}
			}

			friend std::ostream& operator<<(std::ostream& os, const Token& token);

			TokenType GetType() const { return m_Type; }
			char* GetData() { return m_Data.data(); }
			const char* GetData() const { return m_Data.data(); }

		private:
			TokenType m_Type;

			std::optional<Position> m_StartPos;
			std::optional<Position> m_EndPos;

			std::vector<char> m_Data;
		};

	public:
		Tokenizer(std::string fileContent, Compiler& compiler);

	private:
		void Advance();
		void Start();

		void SkipUnknown();
		char NextChar();
		char PreviousChar();

		Token MakeNumber();
		Token MakeIdentifier();
		Token MakeNotEquals();
		Token MakeEquals();
		Token MakeLessThan();
		Token MakeGreaterThan();

	private:
		std::string m_Text;
		Compiler& m_Compiler;
		Position m_Position;
		char m_CurrentChar = '\0';

		// clang-format off
		inline static std::vector<std::string> s_Keywords
		{
			// Data types
			"int", "int2", "int3", "int4",
			"uint", "uint2", "uint3", "uint4",
			"float", "float2", "float3", "float4",
			"matrix", "struct", "uniform"

			// Control blocks
			"if", "else if", "else", "for", "while", "continue", "break",
		};
		// clang-format on

		inline static std::vector<char> s_Letters{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
			'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a',
			'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
			's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '_' };

		inline static std::vector<char> s_Numbers{ '0', '1', '2', '3', '4', '5', '6', '7', '8',
			'9' };

		inline static std::vector<std::string> s_SystemSemantics{ "SV_POSITION" };
	};

}  // namespace At0::Ion
