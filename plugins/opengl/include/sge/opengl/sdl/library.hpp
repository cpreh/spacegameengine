//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_SDL_LIBRARY_HPP_INCLUDED
#define SGE_OPENGL_SDL_LIBRARY_HPP_INCLUDED

#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace sdl
{

class library
{
	FCPPT_NONCOPYABLE(
		library
	);
public:
	library();

	~library();
};

}
}
}

#endif
