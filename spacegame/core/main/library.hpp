#ifndef SGE_LIBRARY_HPP_INCLUDED
#define SGE_LIBRARY_HPP_INCLUDED

#include <string>
#include <stdexcept>
#include <iostream>
#include "./types.hpp"
#include "./bitwise_cast.hpp"

#ifdef SGE_WINDOWS_PLATFORM
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#elif SGE_LINUX_PLATFORM
	#include<dlfcn.h>
#endif

namespace {
	inline const char* liberror()
	{
#ifdef SGE_LINUX_PLATFORM
		return dlerror();
#else
		return "";
#endif
	}
}

namespace sge
{
	class library {
	private:
#ifdef SGE_WINDOWS_PLATFORM
		HMODULE handle;
#elif SGE_LINUX_PLATFORM
		void* handle;
#endif
	public:
		library(const std::string& n)
			:
#ifdef SGE_WINDOWS_PLATFORM
			handle(LoadLibrary(n.c_str()))
#elif SGE_LINUX_PLATFORM
			handle(dlopen(n.c_str(),RTLD_NOW | RTLD_GLOBAL))
#endif
			, n(n)
		{
			if(!handle)
				throw std::runtime_error(std::string("failed to load library: ") + name() + " : " + liberror());
		}

		~library()
		{
			if(handle)
#ifdef SGE_WINDOWS_PLATFORM
				FreeLibrary(handle);
#elif SGE_LINUX_PLATFORM
				dlclose(handle);
#endif
		}

		template<typename Fun>
		Fun load_function(const std::string& fun)
		{
#ifdef SGE_WINDOWS_PLATFORM
			Fun ptr = reinterpret_cast<Fun>(GetProcAddress(handle,fun.c_str()));
#elif SGE_LINUX_PLATFORM
			Fun ptr = bitwise_cast<Fun>(dlsym(handle,fun.c_str()));
#endif
			if(!ptr)
				throw std::runtime_error(std::string("failed to load function ") + fun + " from library " + name() + " : " + liberror());
			return ptr;
		}
		const std::string& name() const { return n; }
	private:
		std::string n;
	};
}

#endif
