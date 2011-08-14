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


#include "../declare_local_logger.hpp"
#include <sge/cegui/detail/geometry_buffer.hpp>
#include <sge/cegui/detail/renderer.hpp>
#include <sge/cegui/detail/texture.hpp>
#include <sge/cegui/detail/texture_target.hpp>
#include <sge/cegui/structure_cast.hpp>
#include <sge/cegui/vf/format.hpp>
#include <sge/renderer/caps.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/onscreen_target.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/draw_mode.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/stencil_func.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/viewport.hpp>
#include <fcppt/algorithm/ptr_container_erase.hpp>
#include <fcppt/assert/error_message.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <algorithm>
#include <CEGUISystem.h>

SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("renderer"))

sge::cegui::detail::renderer::renderer(
	system &_system,
	sge::renderer::device &_renderer)
:
	system_(
		_system),
	renderer_(
		_renderer),
	vertex_declaration_(
		renderer_.create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<vf::format>())),
	// We initialize that later
	display_size_(
		640,480),
	// CEGUI's OpenGL renderer uses 96dpi so I just copied it.
	display_dpi_(
		static_cast<unit>(
			96),
		static_cast<unit>(
			96)),
	identifier_(
		"sge renderer"),
	default_target_(
		renderer_),
	default_root_(
		default_target_),
	geometry_buffers_(),
	texture_targets_(),
	textures_()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("renderer()"));
}

CEGUI::RenderingRoot &
sge::cegui::detail::renderer::getDefaultRenderingRoot()
{
	return default_root_;
}

CEGUI::GeometryBuffer &
sge::cegui::detail::renderer::createGeometryBuffer()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("createGeometryBuffer()"));
	geometry_buffers_.push_back(
		new geometry_buffer(
			renderer_,
			*vertex_declaration_));
	return geometry_buffers_.back();
}

void
sge::cegui::detail::renderer::destroyGeometryBuffer(
	CEGUI::GeometryBuffer const &buffer)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("destroyGeometryBuffer()"));
	FCPPT_ASSERT_ERROR_MESSAGE(
		fcppt::algorithm::ptr_container_erase(
			geometry_buffers_,
			dynamic_cast<geometry_buffer const *>(
				&buffer)),
		FCPPT_TEXT("Tried to destroy a geometry buffer which was not registered"));
}

void
sge::cegui::detail::renderer::destroyAllGeometryBuffers()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("destroyAllGeometryBuffers()"));
	geometry_buffers_.clear();
}

CEGUI::TextureTarget *
sge::cegui::detail::renderer::createTextureTarget()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("createTextureTarget()"));
	texture_targets_.push_back(
		new texture_target(
			system_));
	return &(texture_targets_.back());
}

void
sge::cegui::detail::renderer::destroyTextureTarget(
	CEGUI::TextureTarget *texture)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("destroyTextureTarget(") << texture << FCPPT_TEXT(")"));
	FCPPT_ASSERT_PRE(
		texture);
	FCPPT_ASSERT_ERROR_MESSAGE(
		fcppt::algorithm::ptr_container_erase(
			texture_targets_,
			dynamic_cast<texture_target *>(
				texture)),
		FCPPT_TEXT("Tried to destroy a texture target which was not registered"));
}

void
sge::cegui::detail::renderer::destroyAllTextureTargets()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("destroyAllTextureTargets()"));
	texture_targets_.clear();
}

CEGUI::Texture &
sge::cegui::detail::renderer::createTexture()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("createTexture()"));
	textures_.push_back(
		new texture(
			system_,
			sge::renderer::texture::capabilities_field::null()));
	return textures_.back();
}

CEGUI::Texture &
sge::cegui::detail::renderer::createTexture(
	CEGUI::String const &filename,
	CEGUI::String const &resource_group)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("createTexture(")
			<< fcppt::from_std_string(filename.c_str())
			<< FCPPT_TEXT(", ")
			<< fcppt::from_std_string(resource_group.c_str())
			<< FCPPT_TEXT(")"));
	textures_.push_back(
		new texture(
			system_,
			sge::renderer::texture::capabilities_field::null()));
	textures_.back().loadFromFile(
		filename,
		resource_group);
	return textures_.back();
}

CEGUI::Texture &
sge::cegui::detail::renderer::createTexture(
	CEGUI::Size const &s)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("createTexture(") << structure_cast<sge::renderer::dim2>(s) << FCPPT_TEXT(")"));
	textures_.push_back(
		new texture(
			system_,
			sge::renderer::texture::capabilities_field::null()));
	textures_.back().resize(
		s);
	return textures_.back();
}

void
sge::cegui::detail::renderer::destroyTexture(
	CEGUI::Texture &_texture)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("destroyTexture(") << &_texture << FCPPT_TEXT(")"));
	FCPPT_ASSERT_ERROR_MESSAGE(
		fcppt::algorithm::ptr_container_erase(
			textures_,
			dynamic_cast<texture *>(
				&_texture)),
		FCPPT_TEXT("Tried to destroy a texture which was not registered"));
}

void
sge::cegui::detail::renderer::destroyAllTextures()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("destroyAllTextures()"));
	textures_.clear();
}

void
sge::cegui::detail::renderer::beginRendering()
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
		fcppt::log::_ << FCPPT_TEXT("beginRendering()"));


	renderer_.push_state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::enable_alpha_blending = true)
			(sge::renderer::state::bool_::enable_scissor_test = true)
			(sge::renderer::state::cull_mode::off)
			(sge::renderer::state::depth_func::off)
			(sge::renderer::state::stencil_func::off)
			(sge::renderer::state::draw_mode::fill));
}

#include <sge/renderer/matrix_mode.hpp>
#include <fcppt/foreach_enumerator.hpp>

void
sge::cegui::detail::renderer::endRendering()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("endRendering()"));

	renderer_.pop_state();

	FCPPT_FOREACH_ENUMERATOR(
		index,
		sge::renderer::matrix_mode
	)
		renderer_.transform(
			index,
			sge::renderer::matrix4::identity());
}

void
sge::cegui::detail::renderer::setDisplaySize(
	CEGUI::Size const &_display_size)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("setDisplaySize(")
			<< structure_cast<sge::renderer::dim2>(_display_size)
			<< FCPPT_TEXT(")"));
	display_size_ =
		_display_size;
	// This is what OpenGL does, too, but the default target currently
	// ignores this message
	default_target_.setArea(
		structure_cast(
			renderer_.onscreen_target().viewport().get()));
}

CEGUI::Size const &
sge::cegui::detail::renderer::getDisplaySize() const
{
	return
		display_size_;
}

CEGUI::Vector2 const &
sge::cegui::detail::renderer::getDisplayDPI() const
{
	return
		display_dpi_;
}

CEGUI::uint
sge::cegui::detail::renderer::getMaxTextureSize() const
{
	return
		static_cast<CEGUI::uint>(
			std::min(
				renderer_.caps().max_texture_size().w(),
				renderer_.caps().max_texture_size().h()));
}

CEGUI::String const &
sge::cegui::detail::renderer::getIdentifierString() const
{
	return identifier_;
}

sge::renderer::device &
sge::cegui::detail::renderer::impl() const
{
	return renderer_;
}

sge::cegui::detail::renderer::~renderer()
{
}
