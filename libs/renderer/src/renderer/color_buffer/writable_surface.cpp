//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image2d/view/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/color_buffer/tag_from_dimension.hpp>
#include <sge/renderer/color_buffer/writable_surface.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/impl/buffer/instantiate_writable.hpp>

SGE_RENDERER_IMPL_BUFFER_INSTANTIATE_WRITABLE(sge::renderer::color_buffer::tag_from_dimension<2U>);
