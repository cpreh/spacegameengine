//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TEXTURE_MIPMAP_VARIANT_FWD_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_MIPMAP_VARIANT_FWD_HPP_INCLUDED

#include <sge/renderer/texture/mipmap/all_levels_rep.hpp>
#include <sge/renderer/texture/mipmap/levels_rep.hpp>
#include <sge/renderer/texture/mipmap/off_rep.hpp>
#include <fcppt/variant/variadic_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace texture
{
namespace mipmap
{

typedef
fcppt::variant::variadic<
	sge::renderer::texture::mipmap::off_rep,
	sge::renderer::texture::mipmap::all_levels_rep,
	sge::renderer::texture::mipmap::levels_rep
>
variant;

}
}
}
}

#endif
