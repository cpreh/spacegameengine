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


#ifndef SGE_OPENGL_ONSCREEN_SURFACE_HPP_INCLUDED
#define SGE_OPENGL_ONSCREEN_SURFACE_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/opengl/color_format.hpp>
#include <sge/opengl/color_format_type.hpp>
#include <sge/renderer/lock_mode_fwd.hpp>
#include <sge/renderer/raw_value.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/color_buffer/surface.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/raw_vector_decl.hpp>


namespace sge
{
namespace opengl
{

class onscreen_surface
:
	public sge::renderer::color_buffer::surface
{
	FCPPT_NONCOPYABLE(
		onscreen_surface
	);
public:
	explicit
	onscreen_surface(
		awl::window::object &
	);

	~onscreen_surface();
private:
	sge::renderer::color_buffer::surface::const_view const
	lock(
		sge::renderer::color_buffer::surface::lock_area const &
	) const;

	sge::renderer::color_buffer::surface::view const
	lock(
		sge::renderer::color_buffer::surface::lock_area const &,
		sge::renderer::lock_mode
	);

	void
	unlock() const;

	dim const
	size() const;

	sge::image::color::format
	format() const;

	sge::opengl::color_format const
	color_format() const;

	sge::opengl::color_format_type const
	color_format_type() const;

	typedef fcppt::container::raw_vector<
		sge::renderer::raw_value
	> buffer_type;

	awl::window::object &window_;

	mutable buffer_type buffer_;

	sge::renderer::size_type const stride_;
};

}
}

#endif
