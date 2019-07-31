//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cegui/to_fcppt_string.hpp>
#include <sge/cegui/impl/from_cegui_size.hpp>
#include <sge/cegui/impl/geometry_buffer.hpp>
#include <sge/cegui/impl/renderer.hpp>
#include <sge/cegui/impl/texture.hpp>
#include <sge/cegui/impl/texture_target.hpp>
#include <sge/cegui/impl/to_cegui_rect.hpp>
#include <sge/cegui/impl/to_cegui_vector2.hpp>
#include <sge/cegui/impl/vf/format.hpp>
#include <sge/log/default_parameters.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/to_dpi.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/find_if_opt.hpp>
#include <fcppt/algorithm/remove_if.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/error_message.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/math/box/rect.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/dim/to_vector.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Base.h>
#include <algorithm>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::cegui::impl::renderer::renderer(
	fcppt::log::object &_main_log,
	sge::cegui::impl::texture_parameters const &_texture_parameters
)
:
	main_log_{
		_main_log
	},
	log_{
		_main_log,
		sge::log::default_parameters(
			fcppt::log::name{
				FCPPT_TEXT("renderer")
			}
		)
	},
	texture_parameters_(
		_texture_parameters
	),
	renderer_(
		texture_parameters_.renderer()
	),
	render_context_(),
	vertex_declaration_(
		renderer_.create_vertex_declaration(
			sge::renderer::vertex::declaration_parameters(
				sge::renderer::vf::dynamic::make_format<
					sge::cegui::impl::vf::format
				>()
			)
		)
	),
	// We initialize that later
	display_size_(
		640,
		480
	),
	display_dpi_(
		sge::cegui::impl::to_cegui_vector2(
			fcppt::math::vector::structure_cast<
				fcppt::math::vector::static_<
					CEGUI::Vector2f::value_type,
					2
				>,
				fcppt::cast::size_fun
			>(
				fcppt::math::dim::to_vector(
					sge::renderer::display_mode::to_dpi(
						renderer_.display_mode()
					)
				)
			)
		)
	),
	identifier_(
		"sge renderer"
	),
	default_target_(
		_main_log,
		renderer_,
		render_context_
	),
	geometry_buffers_(),
	texture_targets_(),
	textures_()
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("renderer()")
	)
}

sge::cegui::impl::renderer::~renderer()
{
}

void
sge::cegui::impl::renderer::render_context(
	optional_render_context_ref const &_render_context
)
{
	render_context_ =
		_render_context;
}

sge::renderer::device::ffp &
sge::cegui::impl::renderer::impl() const
{
	return
		renderer_;
}

CEGUI::RenderTarget &
sge::cegui::impl::renderer::getDefaultRenderTarget()
{
	return
		default_target_;
}

CEGUI::GeometryBuffer &
sge::cegui::impl::renderer::createGeometryBuffer()
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("createGeometryBuffer()")
	)

	geometry_buffers_.push_back(
		fcppt::make_unique_ptr<
			sge::cegui::impl::geometry_buffer
		>(
			main_log_,
			renderer_,
			*vertex_declaration_,
			render_context_
		)
	);

	return
		*geometry_buffers_.back();
}

void
sge::cegui::impl::renderer::destroyGeometryBuffer(
	CEGUI::GeometryBuffer const &_buffer
)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("destroyGeometryBuffer()")
	)

	sge::cegui::impl::geometry_buffer const &sge_buffer(
		dynamic_cast<
			sge::cegui::impl::geometry_buffer const &
		>(
			_buffer
		)
	);

	FCPPT_ASSERT_ERROR_MESSAGE(
		fcppt::algorithm::remove_if(
			geometry_buffers_,
			[
				&sge_buffer
			](
				geometry_buffer_unique_ptr const &_element_buffer
			)
			{
				return
					_element_buffer.get_pointer()
					==
					&sge_buffer;
			}
		),
		FCPPT_TEXT("Tried to destroy a geometry buffer which was not registered")
	);
}

void
sge::cegui::impl::renderer::destroyAllGeometryBuffers()
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("destroyAllGeometryBuffers()")
	)

	geometry_buffers_.clear();
}

CEGUI::TextureTarget *
sge::cegui::impl::renderer::createTextureTarget()
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("createTextureTarget()")
	)

	texture_targets_.push_back(
		fcppt::make_unique_ptr<
			sge::cegui::impl::texture_target
		>(
			main_log_,
			texture_parameters_,
			render_context_
		)
	);

	return
		texture_targets_.back().get_pointer();
}

void
sge::cegui::impl::renderer::destroyTextureTarget(
	CEGUI::TextureTarget *_texture
)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("destroyTextureTarget(")
			<< _texture
			<< FCPPT_TEXT(')')
	)

	FCPPT_ASSERT_PRE(
		_texture
	);

	sge::cegui::impl::texture_target &sge_target(
		dynamic_cast<
			sge::cegui::impl::texture_target &
		>(
			*_texture
		)
	);

	FCPPT_ASSERT_ERROR_MESSAGE(
		fcppt::algorithm::remove_if(
			texture_targets_,
			[
				&sge_target
			](
				texture_target_unique_ptr const &_target
			)
			{
				return
					_target.get_pointer()
					==
					&sge_target;
			}
		),
		FCPPT_TEXT("Tried to destroy a texture target which was not registered")
	);
}

void
sge::cegui::impl::renderer::destroyAllTextureTargets()
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("destroyAllTextureTargets()")
	)

	texture_targets_.clear();
}

CEGUI::Texture &
sge::cegui::impl::renderer::createTexture(
	CEGUI::String const &_name
)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("createTexture()")
	)

	return
		this->insert_texture(
			_name,
			fcppt::make_unique_ptr<
				sge::cegui::impl::texture
			>(
				main_log_,
				texture_parameters_,
				_name
			)
		);
}

CEGUI::Texture &
sge::cegui::impl::renderer::createTexture(
	CEGUI::String const &_name,
	CEGUI::String const &_filename,
	CEGUI::String const &_resource_group
)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<<
			FCPPT_TEXT("createTexture(")
			<<
			fcppt::optional::from(
				sge::cegui::to_fcppt_string(
					_filename
				),
				[]{
					return
						fcppt::string{
							FCPPT_TEXT("Failed to convert filename!")
						};
				}
			)
			<<
			FCPPT_TEXT(", ")
			<<
			fcppt::optional::from(
				sge::cegui::to_fcppt_string(
					_resource_group
				),
				[]{
					return
						fcppt::string{
							FCPPT_TEXT("Failed to convert resource group!")
						};
				}
			)
			<<
			FCPPT_TEXT(')')
	)

	CEGUI::Texture &result(
		this->insert_texture(
			_name,
			fcppt::make_unique_ptr<
				sge::cegui::impl::texture
			>(
				main_log_,
				texture_parameters_,
				_name
			)
		)
	);

	result.loadFromFile(
		_filename,
		_resource_group
	);

	return
		result;
}

CEGUI::Texture &
sge::cegui::impl::renderer::createTexture(
	CEGUI::String const &_name,
	CEGUI::Sizef const &_size
)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<<
			FCPPT_TEXT("createTexture(")
			<<
			sge::cegui::impl::from_cegui_size(
				_size
			)
			<<
			FCPPT_TEXT(')')
	)

	return
		this->insert_texture(
			_name,
			fcppt::make_unique_ptr<
				sge::cegui::impl::texture
			>(
				main_log_,
				texture_parameters_,
				_name,
				_size,
				sge::renderer::texture::capabilities_field::null()
			)
		);
}

void
sge::cegui::impl::renderer::destroyTexture(
	CEGUI::Texture &_texture
)
{
	sge::cegui::impl::texture &sge_texture(
		dynamic_cast<
			sge::cegui::impl::texture &
		>(
			_texture
		)
	);

	fcppt::optional::object<
		texture_map::iterator
	> const result{
		fcppt::algorithm::find_if_opt(
			textures_,
			[
				&sge_texture
			](
				texture_map::value_type const &_entry
			)
			{
				return
					_entry.second.get_pointer()
					==
					&sge_texture;
			}
		)
	};

	textures_.erase(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			result
		)
	);
}

void
sge::cegui::impl::renderer::destroyTexture(
	CEGUI::String const &_name
)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<<
			FCPPT_TEXT("destroyTexture(")
			<<
			fcppt::optional::from(
				sge::cegui::to_fcppt_string(
					_name
				),
				[]{
					return
						fcppt::string{
							FCPPT_TEXT("Failed to convert texture name!")
						};
				}
			)
			<< FCPPT_TEXT(')')
	)

	FCPPT_ASSERT_ERROR_MESSAGE(
		textures_.erase(
			_name
		) == 1u,
		FCPPT_TEXT("Tried to destroy a texture by name which was not registered")
	);
}

void
sge::cegui::impl::renderer::destroyAllTextures()
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("destroyAllTextures()")
	)

	textures_.clear();
}

CEGUI::Texture &
sge::cegui::impl::renderer::getTexture(
	CEGUI::String const &_name
) const
{
	return
		*const_cast<
			CEGUI::Texture *
		>(
			static_cast<
				CEGUI::Texture const *
			>(
				FCPPT_ASSERT_OPTIONAL_ERROR(
					fcppt::container::find_opt_mapped(
						textures_,
						_name
					)
				).get().get_pointer()
			)
		);
}

bool
sge::cegui::impl::renderer::isTextureDefined(
	CEGUI::String const &_name
) const
{
	return
		textures_.count(
			_name
		)
		== 1u
		;
}

void
sge::cegui::impl::renderer::beginRendering()
{
	// This is a hack around a bug in cegui: In the "main loop", cegui
	// does the following:
	// beginRendering()
	// ...
	// default_target.activate()
	// default_target.draw()
	// default_target.deactivate()
	// MouseCursor::draw()
	// So if we set the projection matrices in the
	// default_target::activate and reset them in
	// default_target::deactivate, we have no mouse cursor. Hence this
	// projection matrix is set _here_.

	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("beginRendering()")
	)

	FCPPT_ASSERT_PRE(
		render_context_.has_value()
	);
}

void
sge::cegui::impl::renderer::endRendering()
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("endRendering()")
	)

	FCPPT_ASSERT_PRE(
		render_context_.has_value()
	);
}

void
sge::cegui::impl::renderer::setDisplaySize(
	CEGUI::Sizef const &_display_size
)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<<
			FCPPT_TEXT("setDisplaySize(")
			<<
			sge::cegui::impl::from_cegui_size(
				_display_size
			)
			<<
			FCPPT_TEXT(')')
	)

	display_size_ =
		_display_size;

	default_target_.setArea(
		sge::cegui::impl::to_cegui_rect(
			fcppt::math::box::structure_cast<
				fcppt::math::box::rect<
					CEGUI::Rectf::value_type
				>,
				fcppt::cast::int_to_float_fun
			>(
				renderer_.onscreen_target().viewport().get()
			)
		)
	);
}

CEGUI::Sizef const &
sge::cegui::impl::renderer::getDisplaySize() const
{
	return
		display_size_;
}

CEGUI::Vector2f const &
sge::cegui::impl::renderer::getDisplayDPI() const
{
	return
		display_dpi_;
}

CEGUI::uint
sge::cegui::impl::renderer::getMaxTextureSize() const
{
	return
		fcppt::cast::size<
			CEGUI::uint
		>(
			std::min(
				renderer_.caps().max_texture_size().get().w(),
				renderer_.caps().max_texture_size().get().h()
			)
		);
}

CEGUI::String const &
sge::cegui::impl::renderer::getIdentifierString() const
{
	return
		identifier_;
}

CEGUI::Texture &
sge::cegui::impl::renderer::insert_texture(
	CEGUI::String const &_name,
	sge::cegui::impl::renderer::texture_unique_ptr _ptr
)
{
	typedef
	std::pair<
		sge::cegui::impl::renderer::texture_map::iterator,
		bool
	>
	result_type;

	result_type const result(
		textures_.insert(
			std::make_pair(
				_name,
				std::move(
					_ptr
				)
			)
		)
	);

	FCPPT_ASSERT_ERROR(
		result.second
	);

	return
		*result.first->second;
}
