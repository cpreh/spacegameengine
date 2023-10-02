//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/size_type.hpp>
#include <sge/renderer/impl/texture/instantiate_basic_parameters.hpp>
#include <sge/renderer/texture/color_format.hpp>
#include <sge/renderer/texture/cube_parameters.hpp> // NOLINT(misc-include-cleaner)

SGE_RENDERER_IMPL_TEXTURE_INSTANTIATE_BASIC_PARAMETERS(
    sge::renderer::size_type, sge::renderer::texture::color_format);
