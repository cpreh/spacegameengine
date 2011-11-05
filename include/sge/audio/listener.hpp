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


#ifndef SGE_AUDIO_LISTENER_HPP_INCLUDED
#define SGE_AUDIO_LISTENER_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/audio/listener_fwd.hpp>
#include <sge/audio/symbol.hpp>
#include <sge/audio/vector.hpp>
#include <sge/audio/direction/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace audio
{

class SGE_CLASS_SYMBOL listener
{
	FCPPT_NONCOPYABLE(
		listener
	);
protected:
	SGE_AUDIO_SYMBOL explicit
	listener();
public:
	virtual void
	position(
		audio::vector const &) = 0;

	virtual void
	linear_velocity(
		audio::vector const &) = 0;

	virtual void
	direction(
		direction::object const &) = 0;

	SGE_AUDIO_SYMBOL virtual
	~listener() = 0;
};

}
}

#endif
