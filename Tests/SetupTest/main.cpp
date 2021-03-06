#include <Ion/Core/ICompiler.h>

using namespace At0;

#include <string>
#include <vector>
#include <iostream>

#include <fstream>


std::string ReadShader(std::string_view filepath)
{
	std::ifstream reader(filepath.data(), std::ios::ate);

	size_t filesize = reader.tellg();
	reader.seekg(std::ios::beg);

	std::string code;
	code.resize(filesize);

	reader.read(code.data(), filesize);

	return code;
}


int main()
{
	std::string vertexSource = "DefaultShader.vert";
	std::string fragmentSource = "DefaultShader.frag";

	Ion::Compiler compiler;
	compiler.SetErrorCallback(
		[](Ion::Error& error) { std::cout << "Ion error occured: " << error << '\n'; });

	Ion::SourceDescription sourceDesc{};
	sourceDesc.filepath = vertexSource;
	sourceDesc.fileContents = ReadShader(vertexSource);

	Ion::ResultDescription resultDesc{};

	compiler.Compile(sourceDesc, resultDesc);

	std::cout << "\n\n----------------------------\n";
	std::cout << resultDesc.result << '\n';
}