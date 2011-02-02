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
#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/color_surface_ptr.hpp>
#include <sge/renderer/onscreen_target.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/window/instance_ptr.hpp>
#include <fcppt/noncopyable.hpp>

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
	)
public:
	typedef opengl::basic_target<
		sge::renderer::onscreen_target
	> base;

	onscreen_target(
		sge::window::instance_ptr,
		renderer::bit_depth::type
	);

	~onscreen_target();

	void
	bind() const;

	void
	unbind() const;
private:
	renderer::color_surface_ptr const
	surface() const;

	renderer::screen_unit
	height() const;

	sge::renderer::color_surface_ptr const main_surface_;
};

}
}

#endif
