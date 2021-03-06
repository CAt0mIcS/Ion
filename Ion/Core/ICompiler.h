#pragma once

#include "../IBase.h"

#include "../Utils/IError.h"

#include <stdint.h>
#include <string>
#include <vector>


namespace At0::Ion
{
	struct SourceDescription
	{
		std::vector<std::string> sources;
	};

	struct ResultDescription
	{
		std::vector<std::vector<uint32_t>> buffers;
	};


	class ION_EXPORT Compiler
	{
	public:
		Compiler();
		~Compiler();

		Error* Compile(const SourceDescription& sourceDesc, ResultDescription& resultDesc);

	private:
		Scope<Error> m_Error = nullptr;
	};
}  // namespace At0::Ion
