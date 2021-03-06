#pragma once

#ifdef _MSC_VER
	#ifdef ION_BUILD
		#define ION_EXPORT __declspec(dllexport)
	#else
		#define ION_EXPORT __declspec(dllimport)
	#endif
#else
	#define ION_EXPORT
#endif


#include <memory>

namespace At0::Ion
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename... Args>
	Scope<T> MakeScope(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename... Args>
	Ref<T> MakeRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}  // namespace At0::Ray
