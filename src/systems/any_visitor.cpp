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


#include <sge/src/systems/any_visitor.hpp>
#include <sge/src/systems/detail/instance_impl.hpp>
#include <sge/systems/audio_loader_fwd.hpp>
#include <sge/systems/audio_player_fwd.hpp>
#include <sge/systems/charconv_fwd.hpp>
#include <sge/systems/config_fwd.hpp>
#include <sge/systems/font_fwd.hpp>
#include <sge/systems/image2d_fwd.hpp>
#include <sge/systems/input_fwd.hpp>
#include <sge/systems/renderer_fwd.hpp>
#include <sge/systems/window_fwd.hpp>


sge::systems::any_visitor::any_visitor(
	sge::systems::detail::instance_impl &_impl
)
:
	impl_(
		_impl
	)
{
}

sge::systems::any_visitor::result_type
sge::systems::any_visitor::operator()(
	sge::systems::config const &
) const
{
}

sge::systems::any_visitor::result_type
sge::systems::any_visitor::operator()(
	sge::systems::renderer const &_param
) const
{
	impl_.init_renderer(
		_param
	);
}

sge::systems::any_visitor::result_type
sge::systems::any_visitor::operator()(
	sge::systems::window const &_param
) const
{
	impl_.init_window(
		_param
	);
}

sge::systems::any_visitor::result_type
sge::systems::any_visitor::operator()(
	sge::systems::image2d const &_param
) const
{
	impl_.init_image2d(
		_param
	);
}

sge::systems::any_visitor::result_type
sge::systems::any_visitor::operator()(
	sge::systems::audio_loader const &_param
) const
{
	impl_.init_audio_loader(
		_param
	);
}

sge::systems::any_visitor::result_type
sge::systems::any_visitor::operator()(
	sge::systems::audio_player const &_param
) const
{
	impl_.init_audio_player(
		_param
	);
}

sge::systems::any_visitor::result_type
sge::systems::any_visitor::operator()(
	sge::systems::input const &_param
) const
{
	impl_.init_input(
		_param
	);
}

sge::systems::any_visitor::result_type
sge::systems::any_visitor::operator()(
	sge::systems::charconv const &
) const
{
	impl_.init_charconv();
}

sge::systems::any_visitor::result_type
sge::systems::any_visitor::operator()(
	sge::systems::font const &
) const
{
	impl_.init_font();
}
