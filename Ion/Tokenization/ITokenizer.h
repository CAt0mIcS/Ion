#pragma once

#include "../IBase.h"
#include <string.h>


namespace At0::Ion
{
	struct ION_EXPORT Position
	{
	public:
		Position(uint32_t idx, int line, int col);

		void Advance(char currentChar);

		uint32_t index;
		int line;
		int column;
	};

	class ION_EXPORT Tokenizer
	{
	public:
		enum class TokenType
		{
			Int,
			Float,
			Plus,
			Minus,
			Multiply,
			Divide,
			LeftParentheses,
			RightParentheses
		};

		class Token
		{
		public:
			template<typename T>
			Token(TokenType type, T&& value) : m_Type(type)
			{
				m_Value.resize(sizeof(value));
				memcpy(m_Value.data(), &value, sizeof(value));
			}

			TokenType GetType() const { return m_Type; }

			template<typename T>
			T& GetValue()
			{
				return *(T*)m_Value.data();
			}

		private:
			TokenType m_Type;
			std::vector<char> m_Value;
		};

	public:
		Tokenizer(std::string fileContent);

	private:
		void Advance();

	private:
		std::string m_Text;
		Position m_Position;
		char m_CurrentChar = '\0';
	};

}  // namespace At0::Ion
