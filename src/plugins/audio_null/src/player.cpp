/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../player.hpp"
#include "../positional.hpp"
#include "../buffer.hpp"
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/make_shared_ptr.hpp>

sge::audio_null::player::player()
:
	listener_()
{}

sge::audio::listener &
sge::audio_null::player::listener()
{
	return listener_;
}

sge::audio::buffer_ptr const
sge::audio_null::player::create_buffer(
	audio::file_ptr)
{
	return 
		sge::audio::buffer_ptr(
			new buffer());
}

sge::audio::sound::positional_ptr const 
sge::audio_null::player::create_positional_stream(
	audio::file_ptr,
	audio::sound::positional_parameters const &)
{
	return 
		sge::audio::sound::positional_ptr(
			new positional());
}

sge::audio::sound::base_ptr const 
sge::audio_null::player::create_nonpositional_stream(
	audio::file_ptr)
{
	return 
		sge::audio::sound::positional_ptr(
			new positional());
}

sge::audio::player_capabilities_field const
sge::audio_null::player::capabilities() const
{
	return sge::audio::player_capabilities::null;
}
