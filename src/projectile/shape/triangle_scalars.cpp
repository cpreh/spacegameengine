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


#include <sge/projectile/triangle.hpp>
#include <sge/projectile/shape/triangle_sequence.hpp>
#include <sge/projectile/shape/detail/scalar_container.hpp>
#include <sge/src/projectile/declare_local_logger.hpp>
#include <sge/src/projectile/object_extrusion_depth.hpp>
#include <sge/src/projectile/shape/triangle_scalars.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/verbose.hpp>
#include <fcppt/config/external_begin.hpp>
#include <LinearMath/btScalar.h>
#include <array>
#include <fcppt/config/external_end.hpp>


SGE_PROJECTILE_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("triangle_scalars")
)

sge::projectile::shape::detail::scalar_container
sge::projectile::shape::triangle_scalars(
	sge::projectile::shape::triangle_sequence const &_triangles
)
{
	sge::projectile::shape::detail::scalar_container scalars(
		_triangles.size() * 8u * 3u * 3u
	);

	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("constructing triangle mesh with ")
			<< _triangles.size()
			<< FCPPT_TEXT(" triangles"));

	sge::projectile::shape::detail::scalar_container::iterator current_scalar =
		scalars.begin();

	for(
		sge::projectile::triangle const &triangle
		:
		_triangles
	)
	{
		typedef std::array<
			btScalar,
			2
		> extrusion_array;

		extrusion_array const extrusion_depth{{
			static_cast<btScalar>(-sge::projectile::object_extrusion_depth()/2),
			static_cast<btScalar>(sge::projectile::object_extrusion_depth()/2)
		}};

		for(
			btScalar const current_z
			:
			extrusion_depth
		)
		{
			FCPPT_LOG_VERBOSE(
				local_log,
				fcppt::log::_
					<< FCPPT_TEXT("triangle begin"));

			for(
				auto const &current_triangle_point
				:
				triangle
			)
			{
				FCPPT_LOG_VERBOSE(
					local_log,
					fcppt::log::_
						<< FCPPT_TEXT("adding point ")
						<< current_triangle_point[0]
						<< FCPPT_TEXT(',')
						<< current_triangle_point[1]
						<< FCPPT_TEXT(',')
						<< current_z);

				*current_scalar++ = current_triangle_point[0];
				*current_scalar++ = current_triangle_point[1];
				*current_scalar++ = current_z;
			}

			FCPPT_LOG_VERBOSE(
				local_log,
				fcppt::log::_
					<< FCPPT_TEXT("triangle end"));
		}
	}

	return
		scalars;
}
