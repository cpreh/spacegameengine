//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/traits/format_stride.hpp>
#include <sge/image2d/algorithm/copy.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/flipped.hpp>
#include <sge/image2d/view/make.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/sub.hpp>
#include <sge/image2d/view/to_const.hpp>
#include <sge/opengl/texture/basic_buffer_impl.hpp>
#include <sge/opengl/texture/basic_lockable_buffer_impl.hpp>
#include <sge/opengl/texture/buffer_surface_types.hpp>
#include <sge/opengl/texture/color_surface.hpp>
#include <sge/opengl/texture/color_surface_types.hpp>


template
class
sge::opengl::texture::basic_buffer<
	sge::opengl::texture::color_surface_types
>;

template
class
sge::opengl::texture::basic_lockable_buffer<
	sge::opengl::texture::color_surface_types
>;
