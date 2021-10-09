//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_TARGET_FROM_TEXTURE_HPP_INCLUDED
#define SGE_RENDERER_TARGET_FROM_TEXTURE_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/target/offscreen_unique_ptr.hpp>
#include <sge/renderer/texture/planar_ref.hpp>

namespace sge::renderer::target
{

SGE_RENDERER_DETAIL_SYMBOL
sge::renderer::target::offscreen_unique_ptr
    from_texture(sge::renderer::device::core_ref, sge::renderer::texture::planar_ref);

}

#endif
