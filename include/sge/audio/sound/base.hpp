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


#ifndef SGE_AUDIO_SOUND_BASE_HPP_INCLUDED
#define SGE_AUDIO_SOUND_BASE_HPP_INCLUDED

#include <sge/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <sge/audio/scalar.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sge/audio/sound/play_status.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace audio
{
namespace sound
{
class SGE_CLASS_SYMBOL base
{
FCPPT_NONCOPYABLE(base)
public:
	SGE_SYMBOL explicit
	base();

	virtual void 
	play(
		sge::audio::sound::repeat::type) = 0;

	virtual sge::audio::sound::repeat::type
	repeat() const = 0;

	virtual void 
	toggle_pause() = 0;

	virtual play_status::type 
	status() const = 0;

	virtual void 
	gain(
		scalar) = 0;

	virtual scalar 
	gain() const = 0;

	virtual void 
	pitch(
		scalar) = 0;

	virtual scalar 
	pitch() const = 0;

	virtual void 
	stop() = 0;

	virtual void
	update() = 0;

	SGE_SYMBOL virtual
	~base();
};
}
}
}

#endif
