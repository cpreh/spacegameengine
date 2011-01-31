/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_DEFAULT_TARGET_HPP_INCLUDED
#define SGE_OPENGL_DEFAULT_TARGET_HPP_INCLUDED

#include "target.hpp"
#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/color_surface_ptr.hpp>
#include <sge/renderer/color_surface_vector.hpp>
#include <sge/renderer/depth_stencil_surface_ptr.hpp>
#include <sge/renderer/depth_stencil_surface_vector.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/window/instance_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{

class default_target
:
	public opengl::target
{
	FCPPT_NONCOPYABLE(
		default_target
	)
public:
	default_target(
		sge::window::instance_ptr,
		renderer::bit_depth::type
	);

	~default_target();

	void
	bind() const;

	void
	unbind() const;
private:
	void
	add_surface(
		renderer::color_surface_ptr
	);

	void
	remove_surface(
		renderer::color_surface_ptr
	);

	void
	add_surface(
		renderer::depth_stencil_surface_ptr
	);

	void
	remove_surface(
		renderer::depth_stencil_surface_ptr
	);

	renderer::color_surface_vector const
	color_surfaces() const;

	renderer::depth_stencil_surface_vector const
	depth_stencil_surfaces() const;

	renderer::screen_unit
	height() const;

	sge::renderer::color_surface_ptr const main_surface_;
};

}
}

#endif
