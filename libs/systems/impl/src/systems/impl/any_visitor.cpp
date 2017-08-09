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


#include <sge/systems/audio_loader_fwd.hpp>
#include <sge/systems/audio_player_fwd.hpp>
#include <sge/systems/config_fwd.hpp>
#include <sge/systems/font_fwd.hpp>
#include <sge/systems/image2d_fwd.hpp>
#include <sge/systems/input_fwd.hpp>
#include <sge/systems/window_fwd.hpp>
#include <sge/systems/detail/renderer_fwd.hpp>
#include <sge/systems/impl/any_visitor.hpp>
#include <sge/systems/impl/detail/instance_impl.hpp>


sge::systems::impl::any_visitor::any_visitor(
	sge::systems::detail::instance_impl &_impl
)
:
	impl_(
		_impl
	)
{
}

void
sge::systems::impl::any_visitor::operator()(
	sge::systems::config const &
) const
{
}

void
sge::systems::impl::any_visitor::operator()(
	sge::systems::detail::renderer const &_param
) const
{
	impl_.init_renderer(
		_param
	);
}

void
sge::systems::impl::any_visitor::operator()(
	sge::systems::window const &_param
) const
{
	impl_.init_window_object(
		_param
	);
}

void
sge::systems::impl::any_visitor::operator()(
	sge::systems::image2d const &_param
) const
{
	impl_.init_image2d(
		_param
	);
}

void
sge::systems::impl::any_visitor::operator()(
	sge::systems::audio_loader const &_param
) const
{
	impl_.init_audio_loader(
		_param
	);
}

void
sge::systems::impl::any_visitor::operator()(
	sge::systems::audio_player const &_param
) const
{
	impl_.init_audio_player(
		_param
	);
}

void
sge::systems::impl::any_visitor::operator()(
	sge::systems::input const &_param
) const
{
	impl_.init_input(
		_param
	);
}

void
sge::systems::impl::any_visitor::operator()(
	sge::systems::font const &_param
) const
{
	impl_.init_font(
		_param
	);
}
