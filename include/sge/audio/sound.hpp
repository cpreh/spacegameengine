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


#ifndef SGE_AUDIO_SOUND_HPP_INCLUDED
#define SGE_AUDIO_SOUND_HPP_INCLUDED

#include "types.hpp"
#include "play_mode.hpp"
#include "sound_status.hpp"
#include "../math/vector.hpp"
#include "../export.hpp"
#include <boost/noncopyable.hpp>

namespace sge
{
namespace audio
{

class SGE_CLASS_SYMBOL sound : boost::noncopyable {
public:
	virtual void play(play_mode::type) = 0;
	virtual void toggle_pause() = 0;
	virtual sound_status::type status() const = 0;
	virtual void stop() = 0;
	virtual point const pos() const = 0;
	virtual void pos(point const &) = 0;
	virtual bool positional() const = 0;
	virtual void positional(bool) = 0;
	SGE_SYMBOL virtual void update();
	SGE_SYMBOL virtual ~sound();
};

}
}

#endif // SOUND_HPP
