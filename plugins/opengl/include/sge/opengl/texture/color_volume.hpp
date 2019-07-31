//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_COLOR_VOLUME_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_COLOR_VOLUME_HPP_INCLUDED

#include <sge/image/color/traits/format_fwd.hpp>
#include <sge/image3d/traits/color_tag.hpp>
#include <sge/image3d/traits/dimension.hpp>
#include <sge/opengl/texture/basic_buffer.hpp>
#include <sge/opengl/texture/basic_lockable_buffer.hpp>
#include <sge/opengl/texture/color_volume_fwd.hpp>
#include <sge/opengl/texture/color_volume_types.hpp>
#include <sge/renderer/color_buffer/writable_volume.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

extern
template
class
sge::opengl::texture::basic_buffer<
	sge::opengl::texture::color_volume_types
>;

extern
template
class
sge::opengl::texture::basic_lockable_buffer<
	sge::opengl::texture::color_volume_types
>;

FCPPT_PP_POP_WARNING

#endif
