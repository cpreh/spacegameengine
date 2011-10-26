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


#ifndef SGE_D3D9_STATE_DEVICE_HPP_INCLUDED
#define SGE_D3D9_STATE_DEVICE_HPP_INCLUDED

#include <sge/d3d9/state/device_fwd.hpp>
#include <sge/d3d9/state/address_mode.hpp>
#include <sge/d3d9/state/clear.hpp>
#include <sge/d3d9/state/clip_plane.hpp>
#include <sge/d3d9/offscreen_target_fwd.hpp>
#include <sge/d3d9/onscreen_target_fwd.hpp>
#include <sge/d3d9/target_base_fwd.hpp>
#include <sge/renderer/optional_target_fwd.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/stack.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace d3d9
{
namespace state
{

class device
{
	FCPPT_NONCOPYABLE(
		device
	);
public:
	explicit device(
		d3d9::onscreen_target &
	);

	~device();

	void
	target(
		renderer::optional_target const &
	);

	renderer::optional_target const
	target();

	d3d9::state::address_mode &
	address_mode();

	d3d9::state::clear &
	clear();

	d3d9::state::clip_plane &
	clip_plane();

	renderer::state::list &
	current();

	void
	push();

	sge::renderer::state::list const
	pop();
private:
	d3d9::onscreen_target &onscreen_target_;

	d3d9::offscreen_target *offscreen_target_;

	d3d9::target_base *target_;

	d3d9::state::address_mode address_mode_;

	d3d9::state::clear clear_;

	d3d9::state::clip_plane clip_plane_;

	renderer::state::list current_;

	renderer::state::stack stack_;
};

}
}
}

#endif
