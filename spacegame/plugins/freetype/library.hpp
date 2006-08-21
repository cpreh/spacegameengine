#ifndef SGE_FREETYPE_LIBRARY_HPP_INCLUDED
#define SGE_FREETYPE_LIBRARY_HPP_INCLUDED

#include "../../core/main/shared_ptr.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

namespace sge
{
namespace ft
{

struct library {
	library()
	{
		if(FT_Init_FreeType(&impl))
			throw std::runtime_error("FT_Init_FreeType() failed");
	}
	~library()
	{
		FT_Done_FreeType(impl);
	}

	FT_Library impl;
};

}
}

#endif
