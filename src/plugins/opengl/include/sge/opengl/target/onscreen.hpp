/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_TARGET_ONSCREEN_HPP_INCLUDED
#define SGE_OPENGL_TARGET_ONSCREEN_HPP_INCLUDED

#include <sge/opengl/backend/current_fwd.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/target/basic.hpp>
#include <sge/opengl/target/onscreen_fwd.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/color_buffer/readable_surface_fwd.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace opengl
{
namespace target
{

class onscreen
:
	public
		sge::opengl::target::basic<
			sge::renderer::target::onscreen
		>
{
	FCPPT_NONCOPYABLE(
		onscreen
	);
public:
	typedef
	sge::opengl::target::basic<
		sge::renderer::target::onscreen
	>
	base;

	onscreen(
		sge::opengl::context::object &,
		sge::opengl::backend::current &,
		awl::window::object &
	);

	~onscreen()
	override;
private:
	void
	on_bind()
	override;

	void
	on_unbind()
	override;

	void
	end_rendering()
	override;

	sge::renderer::color_buffer::readable_surface const &
	surface() const
	override;

	sge::renderer::screen_unit
	height() const
	override;

	typedef
	fcppt::unique_ptr<
		sge::renderer::color_buffer::readable_surface
	>
	color_surface_unique_ptr;

	sge::opengl::backend::current &current_;

	color_surface_unique_ptr const main_surface_;
};

}
}
}

#endif
