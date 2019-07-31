//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_WGL_VISUAL_PIXEL_FORMAT_TYPES_HPP_INCLUDED
#define SGE_OPENGL_WGL_VISUAL_PIXEL_FORMAT_TYPES_HPP_INCLUDED

#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/wgl/ext.hpp>
#include <sge/opengl/wgl/visual/pixel_format_types_fwd.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


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
	sge::opengl::fun_ref<
		PFNWGLCHOOSEPIXELFORMATARBPROC
	>
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
	sge::opengl::wgl::visual::pixel_format_types::draw_to_window_flag draw_to_window_;

	sge::opengl::wgl::visual::pixel_format_types::support_opengl_flag support_opengl_;

	sge::opengl::wgl::visual::pixel_format_types::double_buffer_flag double_buffer_;

	sge::opengl::wgl::visual::pixel_format_types::pixel_type_flag pixel_type_;

	sge::opengl::wgl::visual::pixel_format_types::pixel_type_rgba_flag pixel_type_rgba_;

	sge::opengl::wgl::visual::pixel_format_types::color_bits_flag color_bits_;

	sge::opengl::wgl::visual::pixel_format_types::depth_bits_flag depth_bits_;

	sge::opengl::wgl::visual::pixel_format_types::stencil_bits_flag stencil_bits_;

	sge::opengl::wgl::visual::pixel_format_types::wgl_choose_pixel_format choose_pixel_format_;
};

}
}
}
}

#endif
