#include "Ipch.h"
#include "ICompiler.h"

#include "Tokenization/ITokenizer.h"


namespace At0::Ion
{
	Compiler::Compiler() {}

	Compiler::~Compiler() {}

	void Compiler::Compile(const SourceDescription& sourceDesc, ResultDescription& resultDesc)
	{
		Tokenizer tokenizer(sourceDesc.fileContents, *this);
	}

	Scope<Error> Compiler::LogError(Scope<Error> error) const
	{
		if (m_ErrorCallback)
		{
			m_ErrorCallback(*error);
		}
		throw std::exception("[Ion] Compilation error occured.");
		return error;
	}
}  // namespace At0::Ion
