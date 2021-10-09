//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_TEXTURE_MIPMAP_ALL_LEVELS_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_MIPMAP_ALL_LEVELS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/texture/mipmap/auto_generate_fwd.hpp>
#include <sge/renderer/texture/mipmap/object.hpp>

namespace sge::renderer::texture::mipmap
{

SGE_RENDERER_DETAIL_SYMBOL
sge::renderer::texture::mipmap::object all_levels(sge::renderer::texture::mipmap::auto_generate);

}

#endif
