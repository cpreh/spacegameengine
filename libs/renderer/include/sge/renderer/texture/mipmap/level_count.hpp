//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TEXTURE_MIPMAP_LEVEL_COUNT_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_MIPMAP_LEVEL_COUNT_HPP_INCLUDED

#include <sge/renderer/texture/mipmap/level_type.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace renderer
{
namespace texture
{
namespace mipmap
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sge::renderer::texture::mipmap::level_type,
	level_count
);

}
}
}
}

#endif
