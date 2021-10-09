//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GUI_CREATE_TEXTURE_HPP_INCLUDED
#define SGE_GUI_CREATE_TEXTURE_HPP_INCLUDED

#include <sge/gui/detail/symbol.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>

namespace sge::gui
{

SGE_GUI_DETAIL_SYMBOL
sge::renderer::texture::planar_unique_ptr
create_texture(sge::renderer::device::core_ref, sge::image2d::view::const_object const &);

}

#endif
