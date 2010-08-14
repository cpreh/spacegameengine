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


#ifndef SGE_OPENAL_SOURCE_HPP_INCLUDED
#define SGE_OPENAL_SOURCE_HPP_INCLUDED

#include "openal.hpp"
#include "source_wrapper.hpp"
#include <sge/audio/sound/positional_parameters.hpp>
#include <sge/audio/sound/play_status.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sge/audio/sound/positional.hpp>
#include <sge/audio/vector.hpp>
#include <sge/audio/scalar.hpp>
#include <fcppt/shared_ptr.hpp>

namespace sge
{
namespace openal
{
class source 
: 
	public audio::sound::positional
{
public:
	explicit
	source(
		ALuint buffer);

	explicit 
	source(
		audio::sound::positional_parameters const &,
		ALuint buffer);

	explicit
	source();

	explicit 
	source(
		audio::sound::positional_parameters const &);

	void 
	play(
		audio::sound::repeat::type);

	void 
	toggle_pause();

	audio::sound::play_status::type 
	status() const;
	
	audio::sound::repeat::type
	repeat() const;

	void 
	stop();

	void 
	update();

	audio::vector const 
	position() const;

	void 
	position(
		audio::vector const &);

	audio::vector const 
	linear_velocity() const;

	void 
	linear_velocity(
		audio::vector const &);

	audio::scalar 
	gain() const;

	void 
	gain(
		audio::scalar);

	audio::scalar 
	pitch() const;

	void 
	pitch(
		audio::scalar);

	audio::scalar 
	rolloff() const;

	void 
	rolloff(
		audio::scalar);

	audio::vector const 
	direction() const;

	void 
	direction(
		audio::vector const &);

	audio::scalar 
	inner_cone_angle() const;

	void 
	inner_cone_angle(
		audio::scalar);

	audio::scalar 
	outer_cone_angle() const;

	void 
	outer_cone_angle(
		audio::scalar);
protected:
	virtual void
	do_play();

	void 
	sync() const;

	ALuint 
	source_id() const;
private:
	source_wrapper source_;
	audio::sound::repeat::type repeat_;
	mutable audio::sound::play_status::type status_;
	audio::vector position_;
	audio::vector direction_;
	audio::vector linear_velocity_;
	audio::scalar gain_;
	audio::scalar pitch_;
	audio::scalar rolloff_;
	audio::scalar inner_cone_angle_;
	audio::scalar outer_cone_angle_;

	void 
	init(
		audio::sound::positional_parameters const &);
	
	void
	positional(
		bool);
};
}
}

#endif
