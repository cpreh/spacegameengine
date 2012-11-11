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


#include <sge/cegui/from_cegui_string.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/vertex_declaration.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/to_dpi.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/src/cegui/declare_local_logger.hpp>
#include <sge/src/cegui/from_cegui_size.hpp>
#include <sge/src/cegui/geometry_buffer.hpp>
#include <sge/src/cegui/renderer.hpp>
#include <sge/src/cegui/texture.hpp>
#include <sge/src/cegui/texture_target.hpp>
#include <sge/src/cegui/to_cegui_rect.hpp>
#include <sge/src/cegui/to_cegui_vector2.hpp>
#include <sge/src/cegui/vf/format.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/move.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/algorithm/ptr_container_erase.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/error_message.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/unreachable_message.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Base.h>
#include <algorithm>
#include <utility>
#include <fcppt/config/external_end.hpp>


SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("renderer")
)

sge::cegui::renderer::renderer(
	sge::cegui::texture_parameters const &_texture_parameters
)
:
	texture_parameters_(
		_texture_parameters
	),
	renderer_(
		texture_parameters_.renderer()
	),
	render_context_(),
	vertex_declaration_(
		renderer_.create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<
				sge::cegui::vf::format
			>()
		)
	),
	// We initialize that later
	display_size_(
		640,
		480
	),
	display_dpi_(
		sge::cegui::to_cegui_vector2<
			CEGUI::Vector2f::value_type
		>(
			sge::renderer::display_mode::to_dpi(
				renderer_.display_mode()
			)
		)
	),
	identifier_(
		"sge renderer"
	),
	default_target_(
		renderer_,
		render_context_
	),
	geometry_buffers_(),
	texture_targets_(),
	textures_()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("renderer()")
	);
}

sge::cegui::renderer::~renderer()
{
}

void
sge::cegui::renderer::render_context(
	optional_render_context_ref const &_render_context
)
{
	render_context_ =
		_render_context;
}

sge::renderer::device::ffp &
sge::cegui::renderer::impl() const
{
	return renderer_;
}

CEGUI::RenderTarget &
sge::cegui::renderer::getDefaultRenderTarget()
{
	return default_target_;
}

CEGUI::GeometryBuffer &
sge::cegui::renderer::createGeometryBuffer()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("createGeometryBuffer()")
	);

	fcppt::container::ptr::push_back_unique_ptr(
		geometry_buffers_,
		fcppt::make_unique_ptr<
			sge::cegui::geometry_buffer
		>(
			fcppt::ref(
				renderer_
			),
			fcppt::cref(
				*vertex_declaration_
			),
			fcppt::cref(
				render_context_
			)
		)
	);

	return
		geometry_buffers_.back();
}

void
sge::cegui::renderer::destroyGeometryBuffer(
	CEGUI::GeometryBuffer const &_buffer
)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("destroyGeometryBuffer()")
	);

	FCPPT_ASSERT_ERROR_MESSAGE(
		fcppt::algorithm::ptr_container_erase(
			geometry_buffers_,
			dynamic_cast<
				geometry_buffer const *
			>(
				&_buffer
			)
		),
		FCPPT_TEXT("Tried to destroy a geometry buffer which was not registered")
	);
}

void
sge::cegui::renderer::destroyAllGeometryBuffers()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("destroyAllGeometryBuffers()")
	);

	geometry_buffers_.clear();
}

CEGUI::TextureTarget *
sge::cegui::renderer::createTextureTarget()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("createTextureTarget()")
	);

	fcppt::container::ptr::push_back_unique_ptr(
		texture_targets_,
		fcppt::make_unique_ptr<
			sge::cegui::texture_target
		>(
			fcppt::cref(
				texture_parameters_
			),
			fcppt::cref(
				render_context_
			)
		)
	);

	return
		&(texture_targets_.back());
}

void
sge::cegui::renderer::destroyTextureTarget(
	CEGUI::TextureTarget *_texture
)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("destroyTextureTarget(")
			<< _texture
			<< FCPPT_TEXT(')')
	);

	FCPPT_ASSERT_PRE(
		_texture
	);

	FCPPT_ASSERT_ERROR_MESSAGE(
		fcppt::algorithm::ptr_container_erase(
			texture_targets_,
			dynamic_cast<
				sge::cegui::texture_target *
			>(
				_texture
			)
		),
		FCPPT_TEXT("Tried to destroy a texture target which was not registered")
	);
}

void
sge::cegui::renderer::destroyAllTextureTargets()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("destroyAllTextureTargets()")
	);

	texture_targets_.clear();
}

CEGUI::Texture &
sge::cegui::renderer::createTexture(
	CEGUI::String const &_name
)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("createTexture()")
	);

	return
		this->insert_texture(
			_name,
			fcppt::make_unique_ptr<
				sge::cegui::texture
			>(
				fcppt::ref(
					texture_parameters_
				),
				_name
			)
		);
}

CEGUI::Texture &
sge::cegui::renderer::createTexture(
	CEGUI::String const &_name,
	CEGUI::String const &_filename,
	CEGUI::String const &_resource_group
)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("createTexture(")
			<< sge::cegui::from_cegui_string(
				_filename,
				texture_parameters_.charconv_system()
			)
			<< FCPPT_TEXT(", ")
			<< sge::cegui::from_cegui_string(
				_resource_group,
				texture_parameters_.charconv_system()
			)
			<< FCPPT_TEXT(')')
	);

	CEGUI::Texture &result(
		this->insert_texture(
			_name,
			fcppt::make_unique_ptr<
				sge::cegui::texture
			>(
				fcppt::ref(
					texture_parameters_
				),
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
sge::cegui::renderer::createTexture(
	CEGUI::String const &_name,
	CEGUI::Sizef const &_size
)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("createTexture(")
			<< sge::cegui::from_cegui_size<
				sge::renderer::dim2
			>(
				_size
			)
			<< FCPPT_TEXT(')')
	);

	return
		this->insert_texture(
			_name,
			fcppt::make_unique_ptr<
				sge::cegui::texture
			>(
				fcppt::ref(
					texture_parameters_
				),
				_name,
				_size,
				sge::renderer::texture::capabilities_field::null()
			)
		);
}

void
sge::cegui::renderer::destroyTexture(
	CEGUI::Texture &_texture
)
{
	sge::cegui::texture *tex(
		&dynamic_cast<
			sge::cegui::texture &
		>(
			_texture
		)
	);

	for(
		sge::cegui::renderer::texture_map::iterator it(
			textures_.begin()
		);
		it != textures_.end();
		++it
	)
		if(
			it->second
			==
			tex
		)
		{
			textures_.erase(
				it
			);

			return;
		}

	FCPPT_ASSERT_UNREACHABLE_MESSAGE(
		FCPPT_TEXT("Tried to destroy a texture by pointer which was not registered")
	);
}

void
sge::cegui::renderer::destroyTexture(
	CEGUI::String const &_name
)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("destroyTexture(")
			<< sge::cegui::from_cegui_string(
				_name,
				texture_parameters_.charconv_system()
			)
			<< FCPPT_TEXT(')')
	);

	FCPPT_ASSERT_ERROR_MESSAGE(
		textures_.erase(
			_name
		) == 1u,
		FCPPT_TEXT("Tried to destroy a texture by name which was not registered")
	);
}

void
sge::cegui::renderer::destroyAllTextures()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("destroyAllTextures()")
	);

	textures_.clear();
}

CEGUI::Texture &
sge::cegui::renderer::getTexture(
	CEGUI::String const &_name
) const
{
	sge::cegui::renderer::texture_map::const_iterator const it(
		textures_.find(
			_name
		)
	);

	FCPPT_ASSERT_ERROR_MESSAGE(
		it != textures_.end(),
		FCPPT_TEXT("Tried to get a texture by name which was not registered")
	);

	return
		*const_cast<
			CEGUI::Texture *
		>(
			static_cast<
				CEGUI::Texture const *
			>(
				it->second
			)
		);
}

bool
sge::cegui::renderer::isTextureDefined(
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
sge::cegui::renderer::beginRendering()
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
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("beginRendering()")
	);

	FCPPT_ASSERT_PRE(
		render_context_
	);
}

void
sge::cegui::renderer::endRendering()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("endRendering()")
	);

	FCPPT_ASSERT_PRE(
		render_context_
	);
}

void
sge::cegui::renderer::setDisplaySize(
	CEGUI::Sizef const &_display_size
)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("setDisplaySize(")
			<< sge::cegui::from_cegui_size<
				sge::renderer::dim2
			>(
				_display_size
			)
			<< FCPPT_TEXT(')')
	);

	display_size_ =
		_display_size;

	// This is what OpenGL does, too, but the default target currently
	// ignores this message
	default_target_.setArea(
		sge::cegui::to_cegui_rect<
			CEGUI::Rectf::value_type
		>(
			renderer_.onscreen_target().viewport().get()
		)
	);
}

CEGUI::Sizef const &
sge::cegui::renderer::getDisplaySize() const
{
	return
		display_size_;
}

CEGUI::Vector2f const &
sge::cegui::renderer::getDisplayDPI() const
{
	return
		display_dpi_;
}

CEGUI::uint
sge::cegui::renderer::getMaxTextureSize() const
{
	return
		static_cast<
			CEGUI::uint
		>(
			std::min(
				renderer_.caps().max_texture_size().get().w(),
				renderer_.caps().max_texture_size().get().h()
			)
		);
}

CEGUI::String const &
sge::cegui::renderer::getIdentifierString() const
{
	return identifier_;
}

CEGUI::Texture &
sge::cegui::renderer::insert_texture(
	CEGUI::String const &_name,
	sge::cegui::renderer::texture_unique_ptr _ptr
)
{
	typedef
	std::pair<
		sge::cegui::renderer::texture_map::iterator,
		bool
	>
	result_type;

	result_type const result(
		fcppt::container::ptr::insert_unique_ptr_map(
			textures_,
			_name,
			fcppt::move(
				_ptr
			)
		)
	);

	FCPPT_ASSERT_ERROR(
		result.second
	);

	return
		*result.first->second;
}
