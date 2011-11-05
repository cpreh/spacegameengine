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

/// The player's listener
/**
 * The listener class is an interface class, you cannot instantiate it. Audio
 * plugins (OpenAL, DirectSound) must derive from this class and create
 * one listener instance per player instance. It's then accessible via the
 * sge::audio::player::listener function.
 *
 * For an introduction to the listener, see \ref audio_positional.
 */
class SGE_CLASS_SYMBOL listener
{
	FCPPT_NONCOPYABLE(
		listener
	);
protected:
	/// Dummy constructor so no instances of this base class can be created
	SGE_AUDIO_SYMBOL explicit
	listener();
public:
	/// Set the position
	virtual void
	position(
		audio::vector const &) = 0;

	/// Set the linear velocity
	virtual void
	linear_velocity(
		audio::vector const &) = 0;

	/// Set the direction
	/**
	 * \note
	 * The direction object might or might not check if it's
	 * actually "correct" in the sense that the vectors are linearly
	 * independent and normalized. Some plugins don't even need linearly
	 * independent/normalized vectors, so they won't correct or check this
	 * either. Be careful.
	 */
	virtual void
	direction(
		direction::object const &) = 0;

	/// Virtual dummy destructor to make it a class to safely derive from.
	/**
	 * Note that this destructor is pure virtual, but has an
	 * implementation. Strictly speaking, that's redundant. But it's safer
	 * for classes which otherwise don't have any pure virtual functions,
	 * yet should be abstract.
	 */
	SGE_AUDIO_SYMBOL virtual
	~listener() = 0;
};

}
}

#endif
