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


#ifndef SGE_OPENGL_ONSCREEN_TARGET_HPP_INCLUDED
#define SGE_OPENGL_ONSCREEN_TARGET_HPP_INCLUDED

#include "onscreen_target_fwd.hpp"
#include "basic_target.hpp"
#include <sge/renderer/onscreen_target.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/window/instance_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sge
{
namespace opengl
{

class onscreen_target
:
	public opengl::basic_target<
		sge::renderer::onscreen_target
	>
{
	FCPPT_NONCOPYABLE(
		onscreen_target
	);
public:
	typedef opengl::basic_target<
		sge::renderer::onscreen_target
	> base;

	explicit onscreen_target(
		sge::window::instance &
	);

	~onscreen_target();
private:
	void
	on_bind();

	void
	on_unbind();

	renderer::color_surface const &
	surface() const;

	renderer::screen_unit
	height() const;

	typedef fcppt::scoped_ptr<
		sge::renderer::color_surface
	> color_surface_scoped_ptr;

	color_surface_scoped_ptr const main_surface_;
};

}
}

#endif
