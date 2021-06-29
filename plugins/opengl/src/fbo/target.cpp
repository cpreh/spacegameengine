//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/fbo/attachment.hpp>
#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/attachment_unique_ptr.hpp>
#include <sge/opengl/fbo/const_render_buffer_ref.hpp>
#include <sge/opengl/fbo/context.hpp>
#include <sge/opengl/fbo/depth_stencil_format_to_attachment.hpp>
#include <sge/opengl/fbo/depth_stencil_surface.hpp>
#include <sge/opengl/fbo/get_config.hpp>
#include <sge/opengl/fbo/last_context.hpp>
#include <sge/opengl/fbo/no_buffer.hpp>
#include <sge/opengl/fbo/render_buffer_binding.hpp>
#include <sge/opengl/fbo/target.hpp>
#include <sge/opengl/fbo/temporary_bind.hpp>
#include <sge/opengl/fbo/texture_binding.hpp>
#include <sge/opengl/fbo/unbind.hpp>
#include <sge/opengl/target/basic_impl.hpp>
#include <sge/opengl/texture/buffer_base.hpp>
#include <sge/opengl/texture/buffer_base_ref.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/color_buffer/optional_surface_ref.hpp>
#include <sge/renderer/color_buffer/surface.hpp>
#include <sge/renderer/depth_stencil_buffer/optional_surface_ref.hpp>
#include <sge/renderer/depth_stencil_buffer/surface.hpp>
#include <sge/renderer/target/offscreen.hpp>
#include <sge/renderer/target/surface_index.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <fcppt/const.hpp>
#include <fcppt/format.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/dynamic_any_fun.hpp>
#include <fcppt/cast/dynamic_cross.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/math/box/null.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/optional/copy_value.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::opengl::fbo::target::target(
	sge::opengl::context::object_ref const _context
)
:
	base(
		_context,
		sge::renderer::target::viewport(
			fcppt::math::box::null<
				sge::renderer::pixel_rect
			>()
		)
	),
	context_(
		sge::opengl::context::use<
			sge::opengl::fbo::context
		>(
			_context,
			_context.get().info()
		)
	),
	config_(
		sge::opengl::fbo::get_config(
			fcppt::make_cref(
				context_
			)
		)
	),
	last_context_(
		sge::opengl::context::use<
			sge::opengl::fbo::last_context
		>(
			_context
		)
	),
	fbo_(
		fcppt::make_ref(
			config_
		)
	),
	height_(),
	color_attachments_(),
	depth_stencil_attachment_()
{
}

sge::opengl::fbo::target::~target()
{
	sge::opengl::fbo::temporary_bind const scoped_exit(
		fcppt::make_cref(
			config_
		),
		fcppt::make_ref(
			last_context_
		),
		fbo_
	);

	depth_stencil_attachment_ =
		optional_attachment_unique_ptr();

	color_attachments_.clear();
}

void
sge::opengl::fbo::target::on_bind()
{
	fbo_.bind();

	last_context_.last_buffer(
		fbo_.id()
	);

	this->check();
}

void
sge::opengl::fbo::target::on_unbind()
{
	sge::opengl::fbo::unbind(
		config_
	);

	last_context_.last_buffer(
		sge::opengl::fbo::no_buffer()
	);
}

void
sge::opengl::fbo::target::end_rendering()
{
}

void
sge::opengl::fbo::target::color_surface(
	sge::renderer::color_buffer::optional_surface_ref const &_opt_surface,
	sge::renderer::target::surface_index const _index
)
{
	sge::opengl::fbo::temporary_bind const scoped_exit(
		fcppt::make_cref(
			config_
		),
		fcppt::make_ref(
			last_context_
		),
		fbo_
	);

	color_attachments_.erase(
		_index
	);

	if(
		_index.get()
		==
		0U
	)
	{
		height_ =
			fcppt::optional::map(
				_opt_surface,
				[](
					fcppt::reference<
						sge::renderer::color_buffer::surface
					> const _surface
				)
				{
					return
						fcppt::cast::size<
							sge::renderer::screen_unit
						>(
							_surface.get().size().h()
						);
				}
			);
	}

	fcppt::optional::maybe_void(
		_opt_surface,
		[
			this,
			_index
		](
			fcppt::reference<
				sge::renderer::color_buffer::surface
			> const _surface
		)
		{
			sge::opengl::texture::buffer_base &texture_surface{
				fcppt::optional::to_exception(
					fcppt::cast::dynamic_cross<
						sge::opengl::texture::buffer_base
					>(
						_surface.get()
					),
					[]{
						return
							sge::renderer::exception{
								FCPPT_TEXT("Color buffer does not derive from opengl::texture::buffer_base!")
							};
					}
				).get()
			};

			if(
				!texture_surface.is_render_target().get()
			)
			{
				throw
					sge::renderer::exception{
						FCPPT_TEXT("You tried to use a texture as a render target ")
						FCPPT_TEXT("which hasn't been created as such!")
					};
			}

			color_attachments_.insert(
				std::make_pair(
					_index,
					this->create_texture_binding(
						fcppt::make_ref(
							texture_surface
						),
						sge::opengl::fbo::attachment_type(
							config_.color_attachment().get()
							+
							_index.get()
						)
					)
				)
			);
		}
	);
}

void
sge::opengl::fbo::target::depth_stencil_surface(
	sge::renderer::depth_stencil_buffer::optional_surface_ref const &_opt_surface
)
{
	sge::opengl::fbo::temporary_bind const scoped_exit(
		fcppt::make_cref(
			config_
		),
		fcppt::make_ref(
			last_context_
		),
		fbo_
	);

	depth_stencil_attachment_ =
		optional_attachment_unique_ptr();

	fcppt::optional::maybe_void(
		_opt_surface,
		[
			this
		](
			fcppt::reference<
				sge::renderer::depth_stencil_buffer::surface
			> const _surface
		)
		{
			sge::opengl::fbo::attachment_type const attachment(
				fcppt::optional::to_exception(
					sge::opengl::fbo::depth_stencil_format_to_attachment(
						config_,
						_surface.get().format()
					),
					[]{
						return
							sge::renderer::unsupported{
								FCPPT_TEXT("depth_stencil_surface target attachment!"),
								FCPPT_TEXT("3.0"),
								FCPPT_TEXT("")
							};
					}
				)
			);

			fcppt::variant::match(
				fcppt::optional::to_exception(
					fcppt::variant::dynamic_cast_<
						fcppt::mpl::list::object<
							sge::opengl::fbo::depth_stencil_surface,
							sge::opengl::texture::buffer_base
						>,
						fcppt::cast::dynamic_any_fun
					>(
						_surface.get()
					),
					[]{
						return
							sge::renderer::exception(
								FCPPT_TEXT("Invalid depth_stencil_surface in add_surface!")
							);
					}
				),
				[
					attachment,
					this
				](
					fcppt::reference<
						sge::opengl::fbo::depth_stencil_surface
					> const _fbo_surface
				)
				{
					depth_stencil_attachment_ =
						optional_attachment_unique_ptr(
							this->create_buffer_binding(
								fcppt::make_ref(
									_fbo_surface.get().render_buffer()
								),
								attachment
							)
						);
				},
				[
					attachment,
					this
				](
					fcppt::reference<
						sge::opengl::texture::buffer_base
					> const _texture_surface
				)
				{
					depth_stencil_attachment_ =
						optional_attachment_unique_ptr(
							this->create_texture_binding(
								_texture_surface,
								attachment
							)
						);
				}
			);
		}
	);
}

sge::renderer::screen_unit
sge::opengl::fbo::target::height() const
{
	return
		fcppt::optional::from(
			height_,
			fcppt::const_(
				fcppt::literal<
					sge::renderer::screen_unit
				>(
					0
				)
			)
		);
}

sge::opengl::fbo::attachment_unique_ptr
sge::opengl::fbo::target::create_texture_binding(
	sge::opengl::texture::buffer_base_ref const _surface,
	sge::opengl::fbo::attachment_type const _attachment
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::opengl::fbo::attachment
		>(
			fcppt::make_unique_ptr<
				sge::opengl::fbo::texture_binding
			>(
				fcppt::make_cref(
					config_
				),
				_surface,
				_attachment
			)
		);
}

sge::opengl::fbo::attachment_unique_ptr
sge::opengl::fbo::target::create_buffer_binding(
	sge::opengl::fbo::const_render_buffer_ref const _buffer,
	sge::opengl::fbo::attachment_type const _attachment
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::opengl::fbo::attachment
		>(
			fcppt::make_unique_ptr<
				sge::opengl::fbo::render_buffer_binding
			>(
				fcppt::make_cref(
					config_
				),
				_buffer,
				_attachment
			)
		);
}

void
sge::opengl::fbo::target::check()
{
	GLenum const status(
		sge::opengl::call_fun_ref(
			config_.check_framebuffer_status(),
			config_.framebuffer_target()
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Checking the fbo status failed."),
		sge::renderer::exception
	)

	if(
		status
		!=
		config_.framebuffer_complete()
	)
	{
		throw
			sge::renderer::exception{
				FCPPT_TEXT("FBO is incomplete! ")
				+
				fcppt::optional::from(
					fcppt::optional::copy_value(
						fcppt::container::find_opt_mapped(
							config_.error_strings(),
							status
						)
					),
					[]{
						return
							fcppt::string{
								FCPPT_TEXT("unknown")
							};
					}
				)
			};
	}
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

template
class
sge::opengl::target::basic<
	sge::renderer::target::offscreen
>;

FCPPT_PP_POP_WARNING
