//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/log/default_parameters.hpp>
#include <sge/projectile/log.hpp>
#include <sge/projectile/log_location.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>


sge::projectile::log::log(
	fcppt::log::context_reference const _log_context
)
:
	world_log_{
		_log_context,
		sge::projectile::log_location(),
		sge::log::default_parameters(
			fcppt::log::name{
				FCPPT_TEXT("world")
			}
		)
	},
	body_log_{
		_log_context,
		sge::projectile::log_location(),
		sge::log::default_parameters(
			fcppt::log::name{
				FCPPT_TEXT("body")
			}
		)
	},
	ghost_log_{
		_log_context,
		sge::projectile::log_location(),
		sge::log::default_parameters(
			fcppt::log::name{
				FCPPT_TEXT("ghost")
			}
		)
	},
	triangle_log_{
		_log_context,
		sge::projectile::log_location(),
		sge::log::default_parameters(
			fcppt::log::name{
				FCPPT_TEXT("triangle_mesh")
			}
		)
	}
{
}

sge::projectile::log::~log()
{
}

fcppt::log::object &
sge::projectile::log::world_log() const
{
	return
		world_log_;
}

fcppt::log::object &
sge::projectile::log::body_log() const
{
	return
		body_log_;
}

fcppt::log::object &
sge::projectile::log::ghost_log() const
{
	return
		ghost_log_;
}

fcppt::log::object &
sge::projectile::log::triangle_log() const
{
	return
		triangle_log_;
}
