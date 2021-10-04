//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TEXTURE_ON_ALLOC_FUNCTION_HPP_INCLUDED
#define SGE_TEXTURE_ON_ALLOC_FUNCTION_HPP_INCLUDED

#include <sge/image/color/format_fwd.hpp>
#include <sge/texture/fragmented_unique_ptr.hpp>


namespace sge::texture
{

using
on_alloc_function
=
sge::texture::fragmented_unique_ptr(
	sge::image::color::format
);

}

#endif
