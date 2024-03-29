//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_TEXTURE_CREATE_PLANAR_FROM_VIEW_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_CREATE_PLANAR_FROM_VIEW_HPP_INCLUDED

#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/texture/emulate_srgb_fwd.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp>

namespace sge::renderer::texture
{

SGE_RENDERER_DETAIL_SYMBOL
sge::renderer::texture::planar_unique_ptr create_planar_from_view(
    sge::renderer::device::core_ref,
    sge::image2d::view::const_object const &,
    sge::renderer::texture::mipmap::object const &,
    sge::renderer::resource_flags_field const &,
    sge::renderer::texture::emulate_srgb);

}

#endif
