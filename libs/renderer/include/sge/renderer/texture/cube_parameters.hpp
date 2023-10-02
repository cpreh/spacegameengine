//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_TEXTURE_CUBE_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_CUBE_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/size_type.hpp>
#include <sge/renderer/texture/basic_parameters.hpp>
#include <sge/renderer/texture/color_format.hpp>
#include <sge/renderer/texture/cube_parameters_fwd.hpp> // IWYU pragma: export
#include <sge/renderer/texture/detail/declare_basic_parameters.hpp>

SGE_RENDERER_TEXTURE_DETAIL_DECLARE_BASIC_PARAMETERS(
    sge::renderer::size_type, sge::renderer::texture::color_format);

#endif
