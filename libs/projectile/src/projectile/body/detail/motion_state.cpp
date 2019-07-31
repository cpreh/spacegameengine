//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/projectile/body/object.hpp>
#include <sge/projectile/impl/body/detail/motion_state.hpp>
#include <fcppt/config/external_begin.hpp>
#include <LinearMath/btMotionState.h>
#include <LinearMath/btTransform.h>
#include <fcppt/config/external_end.hpp>


sge::projectile::body::detail::motion_state::motion_state(
	sge::projectile::body::object &_body
)
:
	btMotionState(),
	body_(
		_body
	)
{
}

sge::projectile::body::detail::motion_state::~motion_state()
{
}

void
sge::projectile::body::detail::motion_state::getWorldTransform(
	btTransform &_transform
) const
{
	body_.getWorldTransform(
		_transform
	);
}

void
sge::projectile::body::detail::motion_state::setWorldTransform(
	btTransform const &_transform
)
{
	body_.setWorldTransform(
		_transform
	);
}
