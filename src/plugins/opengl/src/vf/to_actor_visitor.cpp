/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/vf/actor.hpp>
#include <sge/opengl/vf/actor_parameters.hpp>
#include <sge/opengl/vf/attribute_actor.hpp>
#include <sge/opengl/vf/color_actor.hpp>
#include <sge/opengl/vf/normal_actor.hpp>
#include <sge/opengl/vf/pos_actor.hpp>
#include <sge/opengl/vf/texpos_actor.hpp>
#include <sge/opengl/vf/to_actor_visitor.hpp>
#include <sge/renderer/vf/dynamic/color_fwd.hpp>
#include <sge/renderer/vf/dynamic/extra_fwd.hpp>
#include <sge/renderer/vf/dynamic/normal_fwd.hpp>
#include <sge/renderer/vf/dynamic/pos_fwd.hpp>
#include <sge/renderer/vf/dynamic/texpos_fwd.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::opengl::vf::to_actor_visitor::to_actor_visitor(
	sge::opengl::vf::actor_parameters const &_parameters
)
:
	parameters_(
		_parameters
	)
{
}

sge::opengl::vf::to_actor_visitor::result_type
sge::opengl::vf::to_actor_visitor::operator()(
	sge::renderer::vf::dynamic::pos const &_pos
) const
{
	return
		sge::opengl::vf::actor_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::vf::pos_actor
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
		sge::opengl::vf::actor_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::vf::normal_actor
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
		sge::opengl::vf::actor_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::vf::color_actor
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
		sge::opengl::vf::actor_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::vf::texpos_actor
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
	sge::renderer::vf::dynamic::extra const &_extra
) const
{
	return
		sge::opengl::vf::actor_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::vf::attribute_actor
			>(
				parameters_,
				fcppt::cref(
					_extra
				)
			)
		);
}
