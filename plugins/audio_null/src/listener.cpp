//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/vector_fwd.hpp>
#include <sge/audio/direction/object.hpp>
#include <sge/audio_null/listener.hpp>


sge::audio_null::listener::listener()
= default;

sge::audio_null::listener::~listener()
= default;

void
sge::audio_null::listener::position(
	sge::audio::vector const &
)
{
}

void
sge::audio_null::listener::linear_velocity(
	sge::audio::vector const &
)
{
}

void
sge::audio_null::listener::direction(
	sge::audio::direction::object const &
)
{
}
