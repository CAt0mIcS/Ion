#pragma once

#include "../IBase.h"

#include <exception>
#include <string>
#include <stdint.h>


namespace At0::Ion
{
	class ION_EXPORT Error
	{
	public:
		Error(std::string file, uint32_t line, std::string message);

		ION_EXPORT friend std::ostream& operator<<(std::ostream& os, const Error& error);

		virtual std::string GetType() const = 0;
		virtual ~Error() = default;

	private:
		std::string m_File;
		uint32_t m_Line;
		std::string m_Message;
	};

	class ION_EXPORT TokenizationError : public Error
	{
	public:
		using Error::Error;

		std::string GetType() const override { return "Tokenization Error"; }
	};
}  // namespace At0::Ion
