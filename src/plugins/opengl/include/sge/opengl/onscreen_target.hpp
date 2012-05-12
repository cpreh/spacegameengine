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


#ifndef SGE_OPENGL_ONSCREEN_TARGET_HPP_INCLUDED
#define SGE_OPENGL_ONSCREEN_TARGET_HPP_INCLUDED

#include <sge/opengl/basic_target.hpp>
#include <sge/opengl/onscreen_target_fwd.hpp>
#include <sge/opengl/device_state/object_fwd.hpp>
#include <sge/renderer/color_surface_fwd.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


namespace sge
{
namespace opengl
{

class onscreen_target
:
	public opengl::basic_target<
		sge::renderer::target::onscreen
	>
{
	FCPPT_NONCOPYABLE(
		onscreen_target
	);
public:
	typedef sge::opengl::basic_target<
		sge::renderer::target::onscreen
	> base;

	onscreen_target(
		sge::opengl::device_state::object &,
		awl::window::object &
	);

	~onscreen_target();
private:
	void
	on_bind();

	void
	on_unbind();

	void
	end_rendering();

	sge::renderer::color_surface const &
	surface() const;

	sge::renderer::screen_unit
	height() const;

	typedef fcppt::scoped_ptr<
		sge::renderer::color_surface
	> color_surface_scoped_ptr;

	sge::opengl::device_state::object &device_state_;

	color_surface_scoped_ptr const main_surface_;
};

}
}

#endif
