/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENAL_PLAYER_HPP_INCLUDED
#define SGE_OPENAL_PLAYER_HPP_INCLUDED

#include <sge/audio/buffer_unique_ptr.hpp>
#include <sge/audio/file_fwd.hpp>
#include <sge/audio/listener_fwd.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/scalar.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_unique_ptr.hpp>
#include <sge/openal/context.hpp>
#include <sge/openal/current_context.hpp>
#include <sge/openal/device.hpp>
#include <sge/openal/listener.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace openal
{

class player
:
	public sge::audio::player
{
	FCPPT_NONCOPYABLE(
		player
	);
public:
	player();

	~player();

	sge::audio::listener &
	listener();

	void
	speed_of_sound(
		sge::audio::scalar
	);

	void
	doppler_factor(
		sge::audio::scalar);

	void
	gain(
		sge::audio::scalar);

	sge::audio::buffer_unique_ptr
	create_buffer(
		sge::audio::file &
	);

	sge::audio::sound::positional_unique_ptr
	create_positional_stream(
		sge::audio::file &,
		sge::audio::sound::positional_parameters const &
	);

	sge::audio::sound::base_unique_ptr
	create_nonpositional_stream(
		sge::audio::file &,
		sge::audio::sound::nonpositional_parameters const &
	);

	sge::audio::player_capabilities_field const
	capabilities() const;
private:
	sge::openal::device device_;

	sge::openal::context context_;

	sge::openal::current_context current_context_;

	sge::openal::listener listener_;
};

}
}

#endif
