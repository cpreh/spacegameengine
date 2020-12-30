//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/exception.hpp>
#include <sge/audio/vector_fwd.hpp>
#include <sge/audio/direction/object.hpp>
#include <sge/openal/al.hpp>
#include <sge/openal/listener.hpp>
#include <sge/openal/to_vector3.hpp>
#include <sge/openal/vector3.hpp>
#include <sge/openal/funcs/listener_float_ptr.hpp>
#include <fcppt/array/object_impl.hpp>


sge::openal::listener::listener()
= default;

sge::openal::listener::~listener()
= default;

void
sge::openal::listener::linear_velocity(
	sge::audio::vector const &_vector
)
{
	sge::openal::funcs::listener_float_ptr(
		AL_VELOCITY,
		sge::openal::to_vector3(
			_vector
		).storage().data()
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
		).storage().data()
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

	using
	float6_array
	=
	fcppt::array::object<
		ALfloat,
		6 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	>;

	float6_array const vec{
		forward.x(),
		forward.y(),
		forward.z(),
		up.x(),
		up.y(),
		up.z()
	};

	sge::openal::funcs::listener_float_ptr(
		AL_ORIENTATION,
		vec.data()
	);
}
