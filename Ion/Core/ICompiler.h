#pragma once

#include "../IBase.h"

#include "../Utils/IError.h"

#include <stdint.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>


namespace At0::Ion
{
	struct SourceDescription
	{
		std::string filepath;
		std::string fileContents;
	};

	struct ResultDescription
	{
		std::string result;
	};


	class ION_EXPORT Compiler
	{
		friend class Tokenizer;

	public:
		Compiler();
		~Compiler();

		template<typename T>
		void SetErrorCallback(T&& fn)
		{
			m_ErrorCallback = fn;
		}

		void Compile(const SourceDescription& sourceDesc, ResultDescription& resultDesc);

	private:
		Scope<Error> LogError(Scope<Error> error) const;

	private:
		std::function<void(Error&)> m_ErrorCallback;
	};
}  // namespace At0::Ion
