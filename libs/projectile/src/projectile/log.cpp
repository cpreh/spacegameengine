/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/log/default_parameters.hpp>
#include <sge/projectile/log.hpp>
#include <sge/projectile/log_location.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>


sge::projectile::log::log(
	fcppt::log::context &_log_context
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
