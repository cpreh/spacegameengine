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


#include <sge/audio/exception.hpp>
#include <sge/audio/vector_fwd.hpp>
#include <sge/audio/direction/object.hpp>
#include <sge/openal/al.hpp>
#include <sge/openal/listener.hpp>
#include <sge/openal/to_vector3.hpp>
#include <sge/openal/vector3.hpp>
#include <sge/openal/funcs/listener_float_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


sge::openal::listener::listener()
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
	sge::openal::funcs::listener_float_ptr(
		AL_VELOCITY,
		sge::openal::to_vector3(
			_vector
		).data()
	);
}

void
sge::openal::listener::position(
	sge::audio::vector const &_vector
)
{
	sge::openal::funcs::listener_float_ptr(
		AL_POSITION,
		sge::openal::to_vector3(
			_vector
		).data()
	);
}

void
sge::openal::listener::direction(
	sge::audio::direction::object const &_dir
)
{
	sge::openal::vector3 const forward(
		sge::openal::to_vector3(
			_dir.forward()
		)
	);

	sge::openal::vector3 const up(
		sge::openal::to_vector3(
			_dir.up()
		)
	);

	typedef std::array<
		ALfloat,
		6
	> float6_array;

	float6_array const vec{{
		forward.x(),
		forward.y(),
		forward.z(),
		up.x(),
		up.y(),
		up.z()
	}};

	sge::openal::funcs::listener_float_ptr(
		AL_ORIENTATION,
		vec.data()
	);
}
