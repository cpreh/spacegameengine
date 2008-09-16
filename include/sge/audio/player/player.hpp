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

#include "../../string.hpp"
#include "../../shared_ptr.hpp"
#include "../../plugin/traits.hpp"
#include "../../plugin/capabilities.hpp"
#include "../../export.hpp"
#include "../../math/vector.hpp"
#include "../loader/file.hpp"
#include "sound_angle.hpp"
#include "sound.hpp"

namespace sge
{
namespace audio
{

struct SGE_CLASS_SYMBOL player : boost::noncopyable {
	virtual math::vector3 const listener_pos() const = 0;
	virtual void listener_pos(math::vector3 const &) = 0;
	virtual sound_angle const listener_angle() const = 0;
	virtual void listener_angle(const sound_angle &) = 0;
	virtual const sound_ptr create_nonstream_sound(file_ptr) = 0;
	virtual const sound_ptr create_stream_sound(file_ptr) = 0;
	virtual void update() = 0;
	SGE_SYMBOL virtual ~player();
};

}

namespace plugin
{
namespace detail
{

template<> struct traits<audio::player> {
	SGE_SYMBOL static address_name plugin_loader_name();
	SGE_SYMBOL static capabilities::type get_plugin_type();
	typedef audio::player* (*loader_fun)();
};

}
}

}

#endif // PLAYER_HPP
