//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/vector.hpp>
#include <sge/audio/direction/forward.hpp>
#include <sge/audio/direction/object.hpp>
#include <sge/audio/direction/up.hpp>


sge::audio::direction::object::object(
	sge::audio::direction::forward const &_forward,
	sge::audio::direction::up const &_up
)
:
	forward_(
		_forward.get()
	),
	up_(
		_up.get()
	)
{
}

sge::audio::vector
sge::audio::direction::object::forward() const
{
	return
		forward_;
}

void
sge::audio::direction::object::forward(
	sge::audio::vector const &_forward
)
{
	forward_ =
		_forward;
}

sge::audio::vector
sge::audio::direction::object::up() const
{
	return
		up_;
}

void
sge::audio::direction::object::up(
	sge::audio::vector const &_up
)
{
	up_ =
		_up;
}
