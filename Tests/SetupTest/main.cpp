#include <Ion/Core/ICompiler.h>

using namespace At0;

#include <string>
#include <vector>
#include <iostream>

int main()
{
	std::string vertexSource = "Resources/Shaders/DefaultShader.vert";
	std::string fragmentSource = "Resources/Shaders/DefaultShader.frag";

	Ion::Compiler compiler;

	Ion::SourceDescription sourceDesc{};
	sourceDesc.sources.emplace_back(vertexSource);
	sourceDesc.sources.emplace_back(fragmentSource);
	// ...

	Ion::ResultDescription resultDesc{};

	Ion::Error* error = compiler.Compile(sourceDesc, resultDesc);
	if (error)
	{
		std::cout << "Compilation failed with error: " << error->what() << '\n';
	}
}