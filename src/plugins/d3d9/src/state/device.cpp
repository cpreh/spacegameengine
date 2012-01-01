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


#include <sge/d3d9/offscreen_target.hpp>
#include <sge/d3d9/onscreen_target.hpp>
#include <sge/d3d9/target_base.hpp>
#include <sge/d3d9/state/device.hpp>
#include <sge/renderer/optional_target.hpp>


sge::d3d9::state::device::device(
	d3d9::onscreen_target &_onscreen_target
)
:
	onscreen_target_(
		_onscreen_target
	),
	offscreen_target_(
		0
	),
	target_(
		&_onscreen_target
	),
	clear_(),
	clip_plane_(),
	current_(),
	stack_()
{
}

sge::d3d9::state::device::~device()
{
}

void
sge::d3d9::state::device::target(
	renderer::optional_target const &_target
)
{
	if(
		target_
	)
		target_->active(
			false
		);

	offscreen_target_ =
		_target.has_value()
		?
			&dynamic_cast<
				d3d9::offscreen_target &
			>(
				*_target
			)
		:
			0
		;

	target_ =
		offscreen_target_
		?
			static_cast<
				d3d9::target_base *
			>(
				offscreen_target_
			)
		:
			static_cast<
				d3d9::target_base *
			>(
				&onscreen_target_
			);

	target_->active(
		true
	);
}

sge::renderer::optional_target const
sge::d3d9::state::device::target()
{
	return
		offscreen_target_ != 0
		?
			renderer::optional_target(
				*offscreen_target_
			)
		:
			renderer::optional_target();
}

sge::d3d9::state::clear &
sge::d3d9::state::device::clear()
{
	return clear_;
}

sge::d3d9::state::clip_plane &
sge::d3d9::state::device::clip_plane()
{
	return clip_plane_;
}

sge::renderer::state::list &
sge::d3d9::state::device::current()
{
	return current_;
}

void
sge::d3d9::state::device::push()
{
	stack_.push(
		current_
	);
}

sge::renderer::state::list const
sge::d3d9::state::device::pop()
{
	sge::renderer::state::list const ret(
		stack_.top()
	);

	stack_.pop();

	return ret;
}
