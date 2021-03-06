#include "Ipch.h"
#include "ITokenizer.h"


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

	Tokenizer::Tokenizer(std::string fileContent)
		: m_Text(std::move(fileContent)), m_Position(-1, 0, -1)
	{
		Advance();
	}

	void Tokenizer::Advance()
	{
		m_Position.Advance(m_CurrentChar);
		if (m_Position.index < m_Text.size())
			m_CurrentChar = m_Text[m_Position.index];
		else
			m_CurrentChar = '\0';
	}
}  // namespace At0::Ion