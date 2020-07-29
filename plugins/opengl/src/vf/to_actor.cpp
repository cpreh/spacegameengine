//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_ref.hpp>
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
#include <fcppt/log/object_reference.hpp>
#include <fcppt/variant/match.hpp>


sge::opengl::vf::actor_unique_ptr
sge::opengl::vf::to_actor(
	fcppt::log::object_reference const _log,
	sge::renderer::vf::dynamic::ordered_element const &_element,
	sge::renderer::vf::dynamic::stride const _stride,
	sge::opengl::context::object_ref const _context
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
				_log,
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
							_log,
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
