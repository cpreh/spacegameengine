/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../to_actor_visitor.hpp"
#include "../actor.hpp"
#include "../pos_actor.hpp"
#include "../normal_actor.hpp"
#include "../color_actor.hpp"
#include "../texpos_actor.hpp"
#include "../attribute_actor.hpp"
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>

sge::opengl::vf::to_actor_visitor::to_actor_visitor(
	actor_parameters const &_parameters
)
:
	parameters_(_parameters)
{
}

sge::opengl::vf::to_actor_visitor::result_type
sge::opengl::vf::to_actor_visitor::operator()(
	sge::renderer::vf::dynamic::pos const &_pos
) const
{
	return
		actor_ptr(
			fcppt::make_unique_ptr<
				vf::pos_actor
			>(
				parameters_,
				fcppt::cref(
					_pos
				)
			)
		);
}

sge::opengl::vf::to_actor_visitor::result_type
sge::opengl::vf::to_actor_visitor::operator()(
	sge::renderer::vf::dynamic::normal const &_normal
) const
{
	return
		actor_ptr(
			fcppt::make_unique_ptr<
				vf::normal_actor
			>(
				parameters_,
				fcppt::cref(
					_normal
				)
			)
		);
}

sge::opengl::vf::to_actor_visitor::result_type
sge::opengl::vf::to_actor_visitor::operator()(
	sge::renderer::vf::dynamic::color const &_color
) const
{
	return
		actor_ptr(
			fcppt::make_unique_ptr<
				vf::color_actor
			>(
				parameters_,
				fcppt::cref(
					_color
				)
			)
		);
}

sge::opengl::vf::to_actor_visitor::result_type
sge::opengl::vf::to_actor_visitor::operator()(
	sge::renderer::vf::dynamic::texpos const &_texpos
) const
{
	return
		actor_ptr(
			fcppt::make_unique_ptr<
				vf::texpos_actor
			>(
				parameters_,
				fcppt::cref(
					_texpos
				)
			)
		);
}

sge::opengl::vf::to_actor_visitor::result_type
sge::opengl::vf::to_actor_visitor::operator()(
	sge::renderer::vf::dynamic::unspecified const &_unspecified
) const
{
	return
		actor_ptr(
			fcppt::make_unique_ptr<
				vf::attribute_actor
			>(
				parameters_,
				fcppt::cref(
					_unspecified
				)
			)
		);
}
