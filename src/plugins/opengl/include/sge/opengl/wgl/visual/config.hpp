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


#ifndef SGE_OPENGL_WGL_VISUAL_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_WGL_VISUAL_CONFIG_HPP_INCLUDED

#include <sge/opengl/wgl/extension_set.hpp>
#include <sge/opengl/wgl/scoped_current_fwd.hpp>
#include <sge/opengl/wgl/visual/config_fwd.hpp>
#include <sge/opengl/wgl/visual/optional_pixel_format_types.hpp>
#include <fcppt/optional_impl.hpp>


namespace sge
{
namespace opengl
{
namespace wgl
{
namespace visual
{

class config
{
public:
	config(
		sge::opengl::wgl::extension_set const &,
		sge::opengl::wgl::scoped_current const &
	);

	sge::opengl::wgl::visual::optional_pixel_format_types
	pixel_format_types() const;

	typedef
	fcppt::optional<
		GLint
	>
	optional_int;

	optional_int
	multi_sample_flag() const;

	optional_int
	srgb_flag() const;
private:
	sge::opengl::wgl::visual::optional_pixel_format_types pixel_format_types_;

	optional_int multi_sample_flag_;

	optional_int srgb_flag_;
};

}
}
}
}

#endif
