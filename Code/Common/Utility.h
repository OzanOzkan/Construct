#pragma once

#include <random>
#include <sstream>

namespace Utility
{
	inline std::string generateUUID()
	{
		static std::random_device              rd;
		static std::mt19937                    gen(rd());
		static std::uniform_int_distribution<> dis(0, 15);
		static std::uniform_int_distribution<> dis2(8, 11);

		std::stringstream ss;
		int i;
		ss << std::hex;
		for (i = 0; i < 8; i++) {
			ss << dis(gen);
		}
		ss << "-";
		for (i = 0; i < 4; i++) {
			ss << dis(gen);
		}
		ss << "-4";
		for (i = 0; i < 3; i++) {
			ss << dis(gen);
		}
		ss << "-";
		ss << dis2(gen);
		for (i = 0; i < 3; i++) {
			ss << dis(gen);
		}
		ss << "-";
		for (i = 0; i < 12; i++) {
			ss << dis(gen);
		};
		return ss.str();
	}

#ifdef __GNUG__ // gnu C++ compiler
#include <cxxabi.h>
	inline ::std::string demangle(const char* mangled_name) {

		::std::size_t len = 0;
		int status = 0;
		::std::unique_ptr< char, decltype(&::std::free) > ptr(
			__cxxabiv1::__cxa_demangle(mangled_name, nullptr, &len, &status), &::std::free);
		return ptr.get();
	}
#else
	inline ::std::string demangle(const char* name) { return name; }
#endif // _GNUG_ 

	template <typename T>
	inline ::std::string getObjectName()
	{
		::std::string name = demangle(typeid(T).name());
		return name.substr(name.find(" ") + 1);
	}
}