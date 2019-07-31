//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/activate.hpp>
#include <sge/opengl/texture/active_level.hpp>
#include <sge/opengl/texture/base.hpp>
#include <sge/opengl/texture/bind_context.hpp>
#include <sge/opengl/texture/bind_level.hpp>
#include <sge/opengl/texture/disable.hpp>
#include <sge/opengl/texture/enable.hpp>
#include <sge/opengl/texture/get_stage_type.hpp>
#include <sge/opengl/texture/optional_id.hpp>
#include <sge/opengl/texture/render_binding.hpp>
#include <sge/opengl/texture/set_samplers.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/const_optional_base_ref.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/maybe_void.hpp>


void
sge::opengl::texture::activate(
	fcppt::log::object &_log,
	sge::opengl::context::object &_context,
	sge::renderer::texture::const_optional_base_ref const &_opt_texture,
	sge::renderer::texture::stage const _stage
)
{
	sge::opengl::texture::active_level const active_level(
		_log,
		_context,
		_stage
	);

	sge::opengl::texture::bind_context &bind_context(
		sge::opengl::context::use<
			sge::opengl::texture::bind_context
		>(
			_context
		)
	);

	fcppt::optional::maybe_void(
		sge::opengl::texture::get_stage_type(
			_context,
			_stage
		),
		[
			&active_level,
			&bind_context,
			_stage,
			&_opt_texture
		](
			sge::opengl::texture::type const _old_type
		)
		{
			sge::opengl::texture::disable(
				active_level,
				_old_type
			);

			if(
				!_opt_texture.has_value()
			)
			{
				sge::opengl::texture::bind_level(
					active_level,
					_old_type,
					sge::opengl::texture::optional_id()
				);

				bind_context.stage(
					_stage,
					sge::opengl::texture::const_optional_base_ref()
				);
			}
		}
	);

	fcppt::optional::maybe_void(
		_opt_texture,
		[
			&active_level,
			&bind_context,
			&_context,
			&_stage
		](
			fcppt::reference<
				sge::renderer::texture::base const
			> const _texture
		)
		{
			sge::opengl::texture::base const &base(
				dynamic_cast<
					sge::opengl::texture::base const &
				>(
					_texture.get()
				)
			);

			sge::opengl::texture::enable(
				active_level,
				base.type()
			);

			bind_context.stage(
				_stage,
				sge::opengl::texture::const_optional_base_ref(
					fcppt::make_cref(
						base
					)
				)
			);

			sge::opengl::texture::bind_level(
				active_level,
				base.type(),
				sge::opengl::texture::optional_id(
					base.id()
				)
			);

			sge::opengl::texture::render_binding const binding(
				active_level,
				base.type()
			);

			sge::opengl::texture::set_samplers(
				binding,
				_context
			);
		}
	);
}
