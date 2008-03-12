/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_AUDIO_PLAYER_HPP_INCLUDED
#define SGE_AUDIO_PLAYER_HPP_INCLUDED

// sge
#include "../../string.hpp"
#include "../../shared_ptr.hpp"
#include "../../plugin_traits.hpp"
#include "../../export.hpp"
#include "../../math/vector.hpp"

// Own stuff
#include "../audio_loader/audio_file.hpp"
#include "sound_angle.hpp"

namespace sge
{
class sound;
struct audio_player
{
	virtual math::vector3 listener_pos() const = 0;
	virtual void listener_pos(const math::vector3 &) = 0;
	virtual sound_angle listener_angle() const = 0;
	virtual void listener_angle(const sound_angle &) = 0;
	virtual shared_ptr<sound> create_nonstream_sound(shared_ptr<audio_file>) = 0;
	virtual shared_ptr<sound> create_stream_sound(shared_ptr<audio_file>) = 0;
	virtual void update() = 0;
	virtual ~audio_player() {}
};

namespace detail
{

template<> struct plugin_traits<audio_player> {
	SGE_SYMBOL static address_name plugin_loader_name();
	SGE_SYMBOL static plugin_type::type get_plugin_type();
	typedef audio_player* (*loader_fun)();
};

}
}

#endif // PLAYER_HPP
