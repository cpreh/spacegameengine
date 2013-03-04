/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later versio_vector.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/audio/exception.hpp>
#include <sge/audio/vector.hpp>
#include <sge/audio/direction/object.hpp>
#include <sge/openal/al.hpp>
#include <sge/openal/listener.hpp>
#include <sge/openal/funcs/listener_float_ptr.hpp>


sge::openal::listener::listener()
:
	position_(),
	linear_velocity_()
{
}

sge::openal::listener::~listener()
{
}

void
sge::openal::listener::linear_velocity(
	sge::audio::vector const &_vector
)
{
	linear_velocity_ =
		_vector;

	// TODO: use sge::fcppt::math::vector!
	ALfloat const vec[3] =
		{
			static_cast<ALfloat>(_vector.x()),
			static_cast<ALfloat>(_vector.y()),
			static_cast<ALfloat>(_vector.z())
		};

	sge::openal::funcs::listener_float_ptr(
		AL_VELOCITY,
		vec
	);
}

void
sge::openal::listener::position(
	sge::audio::vector const &_vector
)
{
	position_ = _vector;

	ALfloat const vec[3] =
		{
			static_cast<ALfloat>(_vector.x()),
			static_cast<ALfloat>(_vector.y()),
			static_cast<ALfloat>(_vector.z())
		};

	sge::openal::funcs::listener_float_ptr(
		AL_POSITION,
		vec
	);
}

void
sge::openal::listener::direction(
	sge::audio::direction::object const &_dir
)
{
	ALfloat const vec[6] =
		{
			static_cast<ALfloat>(_dir.forward().x()),
			static_cast<ALfloat>(_dir.forward().y()),
			static_cast<ALfloat>(_dir.forward().z()),
			static_cast<ALfloat>(_dir.up().x()),
			static_cast<ALfloat>(_dir.up().y()),
			static_cast<ALfloat>(_dir.up().z())
		};

	sge::openal::funcs::listener_float_ptr(
		AL_ORIENTATION,
		vec
	);
}
