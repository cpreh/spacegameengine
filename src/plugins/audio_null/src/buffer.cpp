/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/nonpositional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/audio/sound/positional.hpp>
#include <sge/audio/sound/positional_unique_ptr.hpp>
#include <sge/audio_null/buffer.hpp>
#include <sge/audio_null/positional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::audio_null::buffer::buffer()
{
}

sge::audio_null::buffer::~buffer()
{
}

sge::audio::sound::positional_unique_ptr
sge::audio_null::buffer::create_positional(
	sge::audio::sound::positional_parameters const &
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::audio::sound::positional
		>(
			fcppt::make_unique_ptr<
				sge::audio_null::positional
			>()
		);
}

sge::audio::sound::base_unique_ptr
sge::audio_null::buffer::create_nonpositional(
	sge::audio::sound::nonpositional_parameters const &
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::audio::sound::base
		>(
			fcppt::make_unique_ptr<
				sge::audio_null::positional
			>()
		);
}
