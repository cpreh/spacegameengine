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


#include "../device.hpp"
#include "../../offscreen_target.hpp"
#include "../../onscreen_target.hpp"
#include "../../target_base.hpp"

sge::d3d9::state::device::device(
	d3d9::onscreen_target &_onscreen_target
)
:
	onscreen_target_(
		_onscreen_target
	),
	offscreen_target_(),
	target_(
		&_onscreen_target
	),
	address_mode_(),
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
	renderer::target *const _target
)
{
	if(
		_target == offscreen_target_
	)
		return;

	if(
		target_
	)
		target_->active(
			false
		);

	offscreen_target_ =
		dynamic_cast<
			d3d9::offscreen_target *
		>(
			_target
		);

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

sge::renderer::target *
sge::d3d9::state::device::target()
{
	return offscreen_target_;
}

sge::d3d9::state::address_mode &
sge::d3d9::state::device::address_mode()
{
	return address_mode_;
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
