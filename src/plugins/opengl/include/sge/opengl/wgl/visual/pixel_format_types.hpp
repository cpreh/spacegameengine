/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_OPENGL_WGL_VISUAL_PIXEL_FORMAT_TYPES_HPP_INCLUDED
#define SGE_OPENGL_WGL_VISUAL_PIXEL_FORMAT_TYPES_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/wgl/visual/pixel_format_types_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/wglew.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace wgl
{
namespace visual
{

class pixel_format_types
{
	FCPPT_NONASSIGNABLE(
		pixel_format_types
	);
public:
	FCPPT_MAKE_STRONG_TYPEDEF(
		int,
		draw_to_window_flag
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		int,
		support_opengl_flag
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		int,
		double_buffer_flag
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		int,
		pixel_type_flag
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		int,
		pixel_type_rgba_flag
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		int,
		color_bits_flag
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		int,
		depth_bits_flag
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		int,
		stencil_bits_flag
	);

	// Same signature for ARB and EXT
	typedef
	PFNWGLCHOOSEPIXELFORMATARBPROC
	wgl_choose_pixel_format;

	pixel_format_types(
		sge::opengl::wgl::visual::pixel_format_types::draw_to_window_flag,
		sge::opengl::wgl::visual::pixel_format_types::support_opengl_flag,
		sge::opengl::wgl::visual::pixel_format_types::double_buffer_flag,
		sge::opengl::wgl::visual::pixel_format_types::pixel_type_flag,
		sge::opengl::wgl::visual::pixel_format_types::pixel_type_rgba_flag,
		sge::opengl::wgl::visual::pixel_format_types::color_bits_flag,
		sge::opengl::wgl::visual::pixel_format_types::depth_bits_flag,
		sge::opengl::wgl::visual::pixel_format_types::stencil_bits_flag,
		sge::opengl::wgl::visual::pixel_format_types::wgl_choose_pixel_format
	);

	sge::opengl::wgl::visual::pixel_format_types::draw_to_window_flag
	draw_to_window() const;

	sge::opengl::wgl::visual::pixel_format_types::support_opengl_flag
	support_opengl() const;

	sge::opengl::wgl::visual::pixel_format_types::double_buffer_flag
	double_buffer() const;

	sge::opengl::wgl::visual::pixel_format_types::pixel_type_flag
	pixel_type() const;

	sge::opengl::wgl::visual::pixel_format_types::pixel_type_rgba_flag
	pixel_type_rgba() const;

	sge::opengl::wgl::visual::pixel_format_types::color_bits_flag
	color_bits() const;

	sge::opengl::wgl::visual::pixel_format_types::depth_bits_flag
	depth_bits() const;

	sge::opengl::wgl::visual::pixel_format_types::stencil_bits_flag
	stencil_bits() const;

	sge::opengl::wgl::visual::pixel_format_types::wgl_choose_pixel_format
	choose_pixel_format() const;
private:
	sge::opengl::wgl::visual::pixel_format_types::draw_to_window_flag const draw_to_window_;

	sge::opengl::wgl::visual::pixel_format_types::support_opengl_flag const support_opengl_;

	sge::opengl::wgl::visual::pixel_format_types::double_buffer_flag const double_buffer_;

	sge::opengl::wgl::visual::pixel_format_types::pixel_type_flag const pixel_type_;

	sge::opengl::wgl::visual::pixel_format_types::pixel_type_rgba_flag const pixel_type_rgba_;

	sge::opengl::wgl::visual::pixel_format_types::color_bits_flag const color_bits_;

	sge::opengl::wgl::visual::pixel_format_types::depth_bits_flag const depth_bits_;

	sge::opengl::wgl::visual::pixel_format_types::stencil_bits_flag const stencil_bits_;

	sge::opengl::wgl::visual::pixel_format_types::wgl_choose_pixel_format const choose_pixel_format_;
};

}
}
}
}

#endif
