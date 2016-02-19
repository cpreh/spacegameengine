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


#include <sge/gui/impl/renderer/scoped.hpp>
#include <sge/gui/impl/renderer/stateless.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/default_options.hpp>
#include <sge/sprite/state/object_impl.hpp>
#include <sge/sprite/state/parameters_impl.hpp>
#include <sge/sprite/state/scoped_impl.hpp>


sge::gui::impl::renderer::scoped::scoped(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::context::ffp &_context
)
:
	sge::gui::impl::renderer::stateless(
		_renderer
	),
	state_(
		_renderer,
		sge::sprite::state::parameters<
			sprite_state_choices
		>()
	),
	scoped_state_(
		_renderer,
		_context,
		sge::sprite::state::default_options<
			sprite_state_choices
		>(),
		state_
	)
{
}

sge::gui::impl::renderer::scoped::~scoped()
{
}
