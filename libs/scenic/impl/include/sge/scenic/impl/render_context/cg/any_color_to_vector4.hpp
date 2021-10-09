//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_IMPL_RENDER_CONTEXT_CG_ANY_COLOR_TO_VECTOR4_HPP_INCLUDED
#define SGE_SCENIC_IMPL_RENDER_CONTEXT_CG_ANY_COLOR_TO_VECTOR4_HPP_INCLUDED

#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/vector4.hpp>

namespace sge::scenic::impl::render_context::cg
{

sge::renderer::vector4 any_color_to_vector4(sge::image::color::any::object const &);

}

#endif
