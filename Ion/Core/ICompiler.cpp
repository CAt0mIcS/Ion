#include "Ipch.h"
#include "ICompiler.h"


namespace At0::Ion
{
	Compiler::Compiler() {}

	Compiler::~Compiler() {}

	Error* Compiler::Compile(const SourceDescription& sourceDesc, ResultDescription& resultDesc)
	{
		m_Error = MakeScope<CompilerError>("File", 32, "Invalid statement.");

		return m_Error.get();
	}
}  // namespace At0::Ion