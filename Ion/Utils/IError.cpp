#include "Ipch.h"
#include "IError.h"


namespace At0::Ion
{
	Error::Error(std::string file, uint32_t line, std::string message)
		: m_File(std::move(file)), m_Line(line), m_Message(std::move(message))
	{
	}

	const char* Error::what() const
	{
		std::ostringstream oss;
		oss << GetType() << '\n'
			<< "[File] " << m_File << "\n[Line] " << m_Line << "\n[Message] " << m_Message;

		m_WhatBuffer = oss.str();
		return m_WhatBuffer.c_str();
	}
}  // namespace At0::Ion
