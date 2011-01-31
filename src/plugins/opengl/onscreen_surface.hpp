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


#ifndef SGE_OPENGL_ONSCREEN_SURFACE_HPP_INCLUDED
#define SGE_OPENGL_ONSCREEN_SURFACE_HPP_INCLUDED

#include "common.hpp"
#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/color_surface.hpp>
#include <sge/renderer/raw_value.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/window/instance_ptr.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <fcppt/container/raw_vector_decl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{

class onscreen_surface
:
	public sge::renderer::color_surface
{
	FCPPT_NONCOPYABLE(
		onscreen_surface
	)
public:
	onscreen_surface(
		sge::window::instance_ptr,
		renderer::bit_depth::type
	);

	~onscreen_surface();
private:
	image2d::view::const_object const
	lock(
		renderer::lock_rect const &
	) const;

	void
	unlock() const;

	dim_type const
	dim() const;

	GLenum
	format() const;

	GLenum
	format_type() const;

	typedef fcppt::container::raw_vector<
		renderer::raw_value
	> buffer_type;

	sge::window::instance_ptr const window_;

	mutable buffer_type buffer_;

	renderer::size_type const stride_;
};

}
}

#endif
