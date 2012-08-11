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
#include <sge/cegui/to_cegui_string.hpp>
#include <sge/cegui/unit.hpp>
#include <sge/image/const_raw_pointer.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/optional_format.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/pitch.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/capabilities_field_fwd.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/scoped_planar_lock.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/src/cegui/convert_pixel_format.hpp>
#include <sge/src/cegui/declare_local_logger.hpp>
#include <sge/src/cegui/from_cegui_size.hpp>
#include <sge/src/cegui/prefix.hpp>
#include <sge/src/cegui/texel_scaling.hpp>
#include <sge/src/cegui/texture.hpp>
#include <sge/src/cegui/to_absolute_path.hpp>
#include <sge/src/cegui/to_cegui_size.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/unimplemented_message.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Size.h>
#include <CEGUI/String.h>
#include <CEGUI/Texture.h>
#include <CEGUI/Vector.h>
#include <fcppt/config/external_end.hpp>


SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("texture")
)

sge::cegui::texture::texture(
	sge::cegui::texture_parameters const &_texture_parameters,
	CEGUI::String const &_name
)
:
	texture_parameters_(
		_texture_parameters
	),
	name_(
		_name
	),
	size_(),
	texel_scaling_(),
	texture_()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("texture(")
			<< this
			<< FCPPT_TEXT(")::texture(")
			<< sge::cegui::from_cegui_string(
				_name,
				texture_parameters_.charconv_system()
			)
			<< FCPPT_TEXT(')')
	);
}

sge::cegui::texture::texture(
	sge::cegui::texture_parameters const &_texture_parameters,
	CEGUI::String const &_name,
	CEGUI::Sizef const &_size,
	sge::renderer::texture::capabilities_field const &_caps
)
:
	texture_parameters_(
		_texture_parameters
	),
	name_(
		_name
	),
	size_(
		_size
	),
	texel_scaling_(
		sge::cegui::texel_scaling(
			_size
		)
	),
	texture_(
		texture_parameters_.renderer().create_planar_texture(
			sge::renderer::texture::planar_parameters(
				sge::cegui::from_cegui_size<
					sge::renderer::texture::planar::dim
				>(
					*size_
				),
				sge::image::color::format::rgba8,
				sge::renderer::texture::mipmap::off(),
				sge::renderer::resource_flags_field::null(),
				_caps
			)
		)
	)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("texture(")
			<< this
			<< FCPPT_TEXT(")::texture(")
			<< sge::cegui::from_cegui_string(
				_name,
				texture_parameters_.charconv_system()
			)
			<< FCPPT_TEXT(", ")
			<< sge::cegui::from_cegui_size<
				sge::renderer::texture::planar::dim
			>(
				*size_
			)
			<< FCPPT_TEXT(')')
	);
}

sge::cegui::texture::~texture()
{
}

sge::renderer::texture::planar &
sge::cegui::texture::impl()
{
	FCPPT_ASSERT_PRE(
		texture_
	);

	return
		*texture_;
}

void
sge::cegui::texture::create_from_view(
	sge::image2d::view::const_object const &_view
)
{
	FCPPT_ASSERT_PRE(
		!texture_
		&&
		!size_
		&&
		!texel_scaling_
	);

	size_ =
		sge::cegui::texture::optional_sizef(
			sge::cegui::to_cegui_size<
				CEGUI::Sizef::value_type
			>(
				sge::image2d::view::size(
					_view
				)
			)
		);

	texel_scaling_ =
		sge::cegui::texture::optional_vector2f(
			sge::cegui::texel_scaling(
				*size_
			)
		);

	texture_.take(
		sge::renderer::texture::create_planar_from_view(
			texture_parameters_.renderer(),
			_view,
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags_field::null()
		)
	);
}

bool
sge::cegui::texture::empty() const
{
	return
		!texture_;
}

CEGUI::String const  &
sge::cegui::texture::getName() const
{
	return
		name_;
}

CEGUI::Sizef const &
sge::cegui::texture::getSize() const
{
	FCPPT_ASSERT_PRE(
		size_
	);

	return
		*size_;
}

CEGUI::Sizef const &
sge::cegui::texture::getOriginalDataSize() const
{
	return
		this->getSize();
}

CEGUI::Vector2f const &
sge::cegui::texture::getTexelScaling() const
{
	FCPPT_ASSERT_PRE(
		texel_scaling_
	);

	return
		*texel_scaling_;
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
			<< FCPPT_TEXT(')')
	);

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
	void const *const _buffer,
	CEGUI::Sizef const &_buffer_size,
	CEGUI::Texture::PixelFormat const _pixel_format
)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("texture(")
			<< this
			<< FCPPT_TEXT(")::loadFromMemory(")
			<< sge::cegui::from_cegui_size<
				sge::renderer::dim2
			>(
				_buffer_size
			)
			<< FCPPT_TEXT(')')
	);

	FCPPT_ASSERT_PRE(
		texture_
		&&
		size_
		&&
		texel_scaling_
	);

	FCPPT_ASSERT_PRE(
		sge::cegui::from_cegui_size<
			sge::renderer::texture::planar::dim
		>(
			*size_
		)
		==
		sge::cegui::from_cegui_size<
			sge::renderer::texture::planar::dim
		>(
			_buffer_size
		)
	);

	sge::image::color::optional_format const format(
		sge::cegui::convert_pixel_format(
			_pixel_format
		)
	);

	FCPPT_ASSERT_ERROR(
		format
	);

	sge::renderer::texture::scoped_planar_lock const lock(
		*texture_,
		sge::renderer::lock_mode::writeonly
	);

	sge::image2d::algorithm::copy_and_convert(
		sge::image2d::view::make_const(
			static_cast<
				sge::image::const_raw_pointer
			>(
				_buffer
			),
			sge::cegui::from_cegui_size<
				sge::image2d::dim
			>(
				_buffer_size
			),
			*format,
			sge::image2d::pitch::null()
		),
		lock.value(),
		sge::image::algorithm::may_overlap::no
	);
}

void
sge::cegui::texture::blitFromMemory(
	void *,
	CEGUI::Rectf const &
)
{
	// Nothing ever calls this
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("texture::blitFromMemory() is not implemented yet")
	);
}

void
sge::cegui::texture::blitToMemory(
	void *
)
{
	// Nothing ever calls this
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("texture::blitToMemory() is not implemented yet")
	);
}

bool
sge::cegui::texture::isPixelFormatSupported(
	CEGUI::Texture::PixelFormat const _format
) const
{
	return
		sge::cegui::convert_pixel_format(
			_format
		)
		!=
		sge::image::color::optional_format();
}
