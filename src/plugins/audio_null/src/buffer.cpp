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


#include <sge/audio_null/buffer.hpp>
#include <sge/audio_null/positional.hpp>
#include <fcppt/make_shared_ptr.hpp>

sge::audio_null::buffer::buffer()
{
}

sge::audio_null::buffer::~buffer()
{
}

sge::audio::sound::positional_ptr const
sge::audio_null::buffer::create_positional(
	audio::sound::positional_parameters const &
)
{
	return
		audio::sound::positional_ptr(
			fcppt::make_shared_ptr<
				audio_null::positional
			>()
		);
}

sge::audio::sound::base_ptr const
sge::audio_null::buffer::create_nonpositional(
	audio::sound::nonpositional_parameters const &)
{
	return
		audio::sound::base_ptr(
			fcppt::make_shared_ptr<
				audio_null::positional
			>()
		);
}
