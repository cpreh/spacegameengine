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


#include <sge/cegui/exception.hpp>
#include <sge/cegui/from_cegui_string.hpp>
#include <sge/cegui/structure_cast.hpp>
#include <sge/cegui/unit.hpp>
#include <sge/image/const_raw_pointer.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/optional_pitch.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/src/cegui/declare_local_logger.hpp>
#include <sge/src/cegui/prefix.hpp>
#include <sge/src/cegui/texture.hpp>
#include <sge/src/cegui/to_absolute_path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUIImageCodec.h>
#include <CEGUIResourceProvider.h>
#include <CEGUISize.h>
#include <CEGUIString.h>
#include <CEGUITexture.h>
#include <CEGUIVector.h>
#include <fcppt/config/external_end.hpp>


SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("texture")
)

sge::cegui::texture::texture(
	sge::cegui::texture_parameters const &_texture_parameters,
	sge::renderer::texture::capabilities_field const &_caps
)
:
	texture_parameters_(
		_texture_parameters
	),
	caps_(
		_caps
	),
	texture_(),
	size_(
		static_cast<
			sge::cegui::unit
		>(
			0
		),
		static_cast<
			sge::cegui::unit
		>(
			0
		)
	),
	texel_scaling_(
		static_cast<
			sge::cegui::unit
		>(
			1
		),
		static_cast<
			sge::cegui::unit
		>(
			1
		)
	)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("texture(")
			<< this
			<< FCPPT_TEXT(")::texture()")
	);
}

sge::cegui::texture::~texture()
{
}

sge::renderer::texture::planar &
sge::cegui::texture::impl()
{
	return
		*texture_;
}

void
sge::cegui::texture::create_from_view(
	sge::image2d::view::const_object const &_view
)
{
	size_ =
		sge::cegui::structure_cast(
			sge::image2d::view::size(
				_view
			)
		);

	texel_scaling_ =
		CEGUI::Vector2(
			static_cast<
				sge::cegui::unit
			>(
				1
			)
			/
			size_.d_width,
			static_cast<
				sge::cegui::unit
			>(
				1
			)
			/
			size_.d_height
		);

	texture_.take(
		sge::renderer::texture::create_planar_from_view(
			texture_parameters_.renderer(),
			_view,
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags::none
		)
	);
}

bool
sge::cegui::texture::empty() const
{
	return
		static_cast<int>(size_.d_width) == 0
		||
		static_cast<int>(size_.d_height) == 0;
}

CEGUI::Size const &
sge::cegui::texture::getSize() const
{
	return
		size_;
}

CEGUI::Size const &
sge::cegui::texture::getOriginalDataSize() const
{
	return
		size_;
}

CEGUI::Vector2 const &
sge::cegui::texture::getTexelScaling() const
{
	return
		texel_scaling_;
}

void
sge::cegui::texture::resize(
	CEGUI::Size const &_size
)
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
	if(
		this->empty()
	)
	{
		// If the size is zero...no scaling ;)
		texel_scaling_ =
			CEGUI::Vector2(
				static_cast<
					sge::cegui::unit
				>(
					1
				),
				static_cast<
					sge::cegui::unit
				>(
					1
				)
			);
		return;
	}

	texel_scaling_ =
		CEGUI::Vector2(
			static_cast<
				sge::cegui::unit
			>(
				1
			)
			/
			size_.d_width,
			static_cast<
				sge::cegui::unit
			>(
				1
			)
			/
			size_.d_height
		);

	texture_.take(
		texture_parameters_.renderer().create_planar_texture(
			sge::renderer::texture::planar_parameters(
				sge::cegui::structure_cast<
					sge::renderer::dim2
				>(
					_size
				),
				sge::image::color::format::rgba8,
				sge::renderer::texture::mipmap::off(),
				sge::renderer::resource_flags::none,
				caps_
			)
		)
	);
}

void
sge::cegui::texture::loadFromFile(
	CEGUI::String const &_filename,
	CEGUI::String const &_resource_group
)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("texture(")
			<< this
			<< FCPPT_TEXT(")::loadFromFile(")
			<< sge::cegui::from_cegui_string(
				_filename,
				texture_parameters_.charconv_system()
			)
			<< FCPPT_TEXT(", ")
			<< sge::cegui::from_cegui_string(
				_resource_group,
				texture_parameters_.charconv_system()
			)
			<< FCPPT_TEXT(")"));

	this->create_from_view(
		texture_parameters_.image_system().load(
			sge::cegui::to_absolute_path(
				texture_parameters_.charconv_system(),
				texture_parameters_.prefix(),
				_filename
			)
		)->view()
	);
}

void
sge::cegui::texture::loadFromMemory(
	void const * const _buffer,
	CEGUI::Size const &_buffer_size,
	CEGUI::Texture::PixelFormat const _pixel_format
)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("texture(")
			<< this
			<< FCPPT_TEXT(")::loadFromMemory(")
			<< sge::cegui::structure_cast<
				sge::renderer::dim2
			>(
				_buffer_size
			)
			<< FCPPT_TEXT(')')
	);

	FCPPT_ASSERT_PRE(
		this->empty()
	);

	this->create_from_view(
		sge::image2d::view::make_const(
			static_cast<
				sge::image::const_raw_pointer
			>(
				_buffer
			),
			// TODO: Why no structure_cast here?
			sge::image2d::dim(
				static_cast<
					sge::image2d::dim::value_type
				>(
					_buffer_size.d_width
				),
				static_cast<
					sge::image2d::dim::value_type
				>(
					_buffer_size.d_height
				)
			),
			// TODO: own function!
			_pixel_format == PF_RGB
			?
				sge::image::color::format::rgb8
			:
				sge::image::color::format::rgba8
			,
			sge::image2d::view::optional_pitch()
		)
	);
}

void
sge::cegui::texture::saveToMemory(
	void *
)
{
	throw
		sge::cegui::exception(
			FCPPT_TEXT("texture::saveToMemory() is not implemented yet")
		);
}
