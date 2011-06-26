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


#include <sge/audio/pool/sound_data.hpp>

sge::audio::pool::sound_data::sound_data(
	audio::sound::base_ptr const _sound_ptr,
	pool::stop_mode::type const _stop_mode)
:
	sound_ptr_(
		_sound_ptr),
	stop_mode_(
		_stop_mode)
{
}

sge::audio::sound::base_ptr const
sge::audio::pool::sound_data::sound() const
{
	return sound_ptr_;
}

sge::audio::pool::stop_mode::type
sge::audio::pool::sound_data::stop_mode() const
{
	return stop_mode_;
}
