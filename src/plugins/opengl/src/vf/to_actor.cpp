/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/vf/actor.hpp>
#include <sge/opengl/vf/actor_parameters.hpp>
#include <sge/opengl/vf/actor_unique_ptr.hpp>
#include <sge/opengl/vf/attribute_actor.hpp>
#include <sge/opengl/vf/color_actor.hpp>
#include <sge/opengl/vf/normal_actor.hpp>
#include <sge/opengl/vf/pos_actor.hpp>
#include <sge/opengl/vf/texpos_actor.hpp>
#include <sge/opengl/vf/to_actor.hpp>
#include <sge/renderer/vf/dynamic/color_fwd.hpp>
#include <sge/renderer/vf/dynamic/extra_fwd.hpp>
#include <sge/renderer/vf/dynamic/normal_fwd.hpp>
#include <sge/renderer/vf/dynamic/ordered_element.hpp>
#include <sge/renderer/vf/dynamic/pos_fwd.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <sge/renderer/vf/dynamic/texpos_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/variant/match.hpp>


sge::opengl::vf::actor_unique_ptr
sge::opengl::vf::to_actor(
	sge::renderer::vf::dynamic::ordered_element const &_element,
	sge::renderer::vf::dynamic::stride const _stride,
	sge::opengl::context::object &_context
)
{
	sge::opengl::vf::actor_parameters const parameters(
		_stride,
		_element.offset(),
		_context
	);

	return
		fcppt::variant::match(
			_element.element().info(),
			[
				&parameters
			](
				sge::renderer::vf::dynamic::pos const &_pos
			)
			{
				return
					fcppt::unique_ptr_to_base<
						sge::opengl::vf::actor
					>(
						fcppt::make_unique_ptr<
							sge::opengl::vf::pos_actor
						>(
							parameters,
							_pos
						)
					);
			},
			[
				&parameters
			](
				sge::renderer::vf::dynamic::normal const &_normal
			)
			{
				return
					fcppt::unique_ptr_to_base<
						sge::opengl::vf::actor
					>(
						fcppt::make_unique_ptr<
							sge::opengl::vf::normal_actor
						>(
							parameters,
							_normal
						)
					);
			},
			[
				&parameters
			](
				sge::renderer::vf::dynamic::color const &_color
			)
			{
				return
					fcppt::unique_ptr_to_base<
						sge::opengl::vf::actor
					>(
						fcppt::make_unique_ptr<
							sge::opengl::vf::color_actor
						>(
							parameters,
							_color
						)
					);
			},
			[
				&parameters
			](
				sge::renderer::vf::dynamic::texpos const &_texpos
			)
			{
				return
					fcppt::unique_ptr_to_base<
						sge::opengl::vf::actor
					>(
						fcppt::make_unique_ptr<
							sge::opengl::vf::texpos_actor
						>(
							parameters,
							_texpos
						)
					);
			},
			[
				&parameters
			](
				sge::renderer::vf::dynamic::extra const &_extra
			)
			{
				return
					fcppt::unique_ptr_to_base<
						sge::opengl::vf::actor
					>(
						fcppt::make_unique_ptr<
							sge::opengl::vf::attribute_actor
						>(
							parameters,
							_extra
						)
					);
			}
		);
}
