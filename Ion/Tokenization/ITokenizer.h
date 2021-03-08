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
			// Int,
			// Int2,
			// Int3,
			// Int4,
			// Int2x2,
			// Int3x3,
			// Int4x4,

			// UInt,
			// UInt2,
			// UInt3,
			// UInt4,
			// UInt2x2,
			// UInt3x3,
			// UInt4x4,

			// Float,
			// Float2,
			// Float3,
			// Float4,
			// Float2x2,
			// Float3x3,
			// Float4x4,

			// Matrix,

			Plus,
			Minus,
			Multiply,
			Divide,
			LeftParentheses,
			RightParentheses,
			Equal,

			Identifier,
			Keyword,

			Function,

			EndOfFile
		};


	public:
		Tokenizer(std::string fileContent);

	private:
		void Advance();

	private:
		std::string m_Text;
		Position m_Position;
		char m_CurrentChar = '\0';

		// clang-format off
		inline static std::vector<const char*> s_Keywords
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

		inline static std::vector<const char*> s_Letters{ "A", "B", "C", "D", "E", "F", "G", "H",
			"I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y",
			"Z", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p",
			"q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };

		inline static std::vector<const char*> s_Numbers{ "0", "1", "2", "3", "4", "5", "6", "7",
			"8", "9" };
	};

}  // namespace At0::Ion
