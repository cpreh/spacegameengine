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
#include <sge/cegui/detail/texture.hpp>
#include <sge/cegui/system.hpp>
#include <sge/cegui/unit.hpp>
#include <sge/cegui/exception.hpp>
#include <sge/cegui/structure_cast.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/address_mode.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/device.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/optional_pitch.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/const_raw_pointer.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/from_std_string.hpp>
// FFFFFFFFFFFFFFFFUUUUUUUUUUUUUUUUUUUUUUUU
#include <fcppt/optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUIResourceProvider.h>
#include <CEGUIImageCodec.h>
#include <fcppt/config/external_end.hpp>

SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("texture"))

sge::cegui::detail::texture::texture(
	system &_system,
	sge::renderer::texture::capabilities_field const &_caps)
:
	system_(
		_system),
	caps_(
		_caps),
	texture_(),
	size_(
		static_cast<unit>(
			0),
		static_cast<unit>(
			0)),
	texel_scaling_(
		static_cast<unit>(
			1),
		static_cast<unit>(
			1))
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("texture(") << this << FCPPT_TEXT(")::texture()"));
}

bool
sge::cegui::detail::texture::empty() const
{
	return !static_cast<int>(size_.d_width) || !static_cast<int>(size_.d_height);
}

CEGUI::Size const &
sge::cegui::detail::texture::getSize() const
{
	return
		size_;
}

CEGUI::Size const &
sge::cegui::detail::texture::getOriginalDataSize() const
{
	return
		size_;
}

CEGUI::Vector2 const &
sge::cegui::detail::texture::getTexelScaling() const
{
	return
		texel_scaling_;
}

void
sge::cegui::detail::texture::resize(
	CEGUI::Size const &_size)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("texture(")
			<< this
			<< FCPPT_TEXT(")::resize(")
			<< _size.d_width
			<< FCPPT_TEXT("x")
			<< _size.d_height
			<< FCPPT_TEXT(")"));

	size_ =
		_size;

	// The size here could be (0,0), for example if the viewport hasn't
	// been initialized yet. So do nothing in this case
	if(empty())
	{
		// If the size is zero...no scaling ;)
		texel_scaling_ =
			CEGUI::Vector2(
				static_cast<unit>(1),
				static_cast<unit>(1));
		return;
	}

	texel_scaling_ =
		CEGUI::Vector2(
			static_cast<unit>(1)/size_.d_width,
			static_cast<unit>(1)/size_.d_height);

	texture_ =
		system_.renderer().create_planar_texture(
			sge::renderer::texture::planar_parameters(
				structure_cast<sge::renderer::dim2>(
					_size),
				sge::image::color::format::rgba8,
				sge::renderer::texture::mipmap::off(),
				sge::renderer::texture::address_mode2(
					sge::renderer::texture::address_mode::clamp),
				sge::renderer::resource_flags::none,
				caps_));
}

void
sge::cegui::detail::texture::loadFromFile(
	CEGUI::String const &filename,
	CEGUI::String const &resource_group)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("texture(")
			<< this
			<< FCPPT_TEXT(")::loadFromFile(")
			<< fcppt::from_std_string(filename.c_str())
			<< FCPPT_TEXT(", ")
			<< fcppt::from_std_string(resource_group.c_str())
			<< FCPPT_TEXT(")"));

	create_from_view(
		system_.image_loader().load(
			system_.to_absolute_path(
				filename,
				resource_group))->view());
}

void
sge::cegui::detail::texture::loadFromMemory(
	void const * const buffer,
	CEGUI::Size const &buffer_size,
	CEGUI::Texture::PixelFormat const pixel_format)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("texture(")
			<< this
			<< FCPPT_TEXT(")::loadFromMemory(")
			<< structure_cast<sge::renderer::dim2>(buffer_size)
			<< FCPPT_TEXT(")"));

	FCPPT_ASSERT_PRE(
		static_cast<int>(buffer_size.d_width) && static_cast<int>(buffer_size.d_height));

	create_from_view(
		sge::image2d::view::make_const(
			static_cast<sge::image::const_raw_pointer>(
				buffer),
			sge::image2d::dim(
				static_cast<sge::image2d::dim::value_type>(
					buffer_size.d_width),
				static_cast<sge::image2d::dim::value_type>(
					buffer_size.d_height)),
			pixel_format == PF_RGB
			?
				sge::image::color::format::rgb8
			:
				sge::image::color::format::rgba8,
			sge::image2d::view::optional_pitch()));
}

void
sge::cegui::detail::texture::create_from_view(
	sge::image2d::view::const_object const &v)
{
	size_ =
		structure_cast(
			sge::image2d::view::size(
				v));
	texel_scaling_ =
		CEGUI::Vector2(
			static_cast<unit>(1)/size_.d_width,
			static_cast<unit>(1)/size_.d_height);
	texture_ =
		sge::renderer::texture::create_planar_from_view(
			system_.renderer(),
			v,
			sge::renderer::texture::mipmap::off(),
			sge::renderer::texture::address_mode2(
				sge::renderer::texture::address_mode::clamp),
			sge::renderer::resource_flags::none);
}

void
sge::cegui::detail::texture::saveToMemory(
	void*)
{
	throw
		cegui::exception(
			FCPPT_TEXT("texture::saveToMemory() is not implemented yet"));
}

sge::renderer::texture::planar &
sge::cegui::detail::texture::impl()
{
	return *texture_;
}

sge::cegui::detail::texture::~texture()
{
}


