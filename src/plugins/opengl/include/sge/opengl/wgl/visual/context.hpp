/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_WGL_VISUAL_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_WGL_VISUAL_CONTEXT_HPP_INCLUDED

#include <sge/opengl/optional_int.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/wgl/visual/context_fwd.hpp>
#include <sge/opengl/wgl/visual/optional_pixel_format_types.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace wgl
{
namespace visual
{

class context
:
	public sge::opengl::context::system::base
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	context();

	~context();

	sge::opengl::wgl::visual::optional_pixel_format_types const
	pixel_format_types() const;

	sge::opengl::optional_int const
	multi_sample_flag() const;

	sge::opengl::optional_int const
	srgb_flag() const;

	typedef void needs_before;

	static
	sge::opengl::context::system::id const
	static_id;
private:
	sge::opengl::wgl::visual::optional_pixel_format_types const pixel_format_types_;

	sge::opengl::optional_int const multi_sample_flag_;

	sge::opengl::optional_int const srgb_flag_;
};

}
}
}
}

#endif
