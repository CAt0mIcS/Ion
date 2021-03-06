#pragma once

#include "../IBase.h"

#include <exception>
#include <string>
#include <stdint.h>


namespace At0::Ion
{
	class ION_EXPORT Error : public std::exception
	{
	public:
		Error(std::string file, uint32_t line, std::string message);

		const char* what() const override;

		virtual std::string GetType() const = 0;
		virtual ~Error() = default;

	private:
		std::string m_File;
		uint32_t m_Line;
		std::string m_Message;

		mutable std::string m_WhatBuffer;
	};

	class ION_EXPORT CompilerError : public Error
	{
	public:
		using Error::Error;

		std::string GetType() const override { return "CompileError"; }
	};
}  // namespace At0::Ion
