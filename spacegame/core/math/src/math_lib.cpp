#include "../math_lib.hpp"

bool sge::math_lib::initialized(false);
bool sge::math_lib::sse_available(false);

void sge::math_lib::init()
{
	if(initialized)
		return;
#ifdef _MSC_VER
	_asm
	{
		mov eax, 1
		CPUID
		test edx, 00800000h
		jz _EXIT
		mov sse_available, 1
		_EXIT:
	}
#endif
	initialized = true;
}

bool sge::math_lib::sse_avail() { return sse_available; }
