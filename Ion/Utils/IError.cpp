#include "Ipch.h"
#include "IError.h"


namespace At0::Ion
{
	Error::Error(std::string file, uint32_t line, std::string message)
		: m_File(std::move(file)), m_Line(line), m_Message(std::move(message))
	{
	}

	std::ostream& operator<<(std::ostream& os, const Error& error)
	{
		os << error.GetType() << '\n'
		   << "[File] " << error.m_File << "\n[Line] " << error.m_Line << "\n[Message] "
		   << error.m_Message;

		return os;
	}
}  // namespace At0::Ion
