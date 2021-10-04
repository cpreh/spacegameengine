//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_EXTEND_SIZE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_EXTEND_SIZE_HPP_INCLUDED

#include <sge/renderer/dim2_fwd.hpp>
#include <sge/renderer/size_type.hpp>


namespace sge::opengl::texture
{

template<
	typename Size
>
inline
Size
extend_size(
	Size const &_size
)
{
	return
		_size;
}

sge::renderer::dim2
extend_size(
	sge::renderer::size_type
);

}

#endif
