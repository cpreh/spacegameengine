//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/projectile/log.hpp>
#include <sge/projectile/ghost/parameters.hpp>
#include <sge/projectile/ghost/position.hpp>
#include <sge/projectile/ghost/size.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::projectile::ghost::parameters::parameters(
	sge::projectile::log const &_log,
	sge::projectile::ghost::position _position,
	sge::projectile::ghost::size _size
)
:
	log_{
		_log.ghost_log()
	},
	position_(
		std::move(
			_position
		)
	),
	size_(
		std::move(
			_size
		)
	)
{
}

fcppt::log::object &
sge::projectile::ghost::parameters::log() const
{
	return
		log_.get();
}

sge::projectile::ghost::position const &
sge::projectile::ghost::parameters::position() const
{
	return
		position_;
}

sge::projectile::ghost::size const &
sge::projectile::ghost::parameters::size() const
{
	return
		size_;
}
