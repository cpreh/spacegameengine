//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_TEXTURE_VOLUME_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_VOLUME_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/dim3.hpp>
#include <sge/renderer/texture/color_format.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp> // IWYU pragma: export
#include <sge/renderer/texture/detail/declare_basic_parameters.hpp>

SGE_RENDERER_TEXTURE_DETAIL_DECLARE_BASIC_PARAMETERS(
    sge::renderer::dim3, sge::renderer::texture::color_format);

#endif
