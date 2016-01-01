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


#include <sge/cegui/from_cegui_string.hpp>
#include <sge/cegui/to_cegui_string.hpp>
#include <sge/cegui/unit.hpp>
#include <sge/image/const_raw_pointer.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/optional_format.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/load_exn.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/pitch.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/texture/capabilities_field_fwd.hpp>
#include <sge/renderer/texture/color_format.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
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
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/unimplemented_message.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/null.hpp>
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
				_name
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
					_size
				),
				sge::renderer::texture::color_format(
					sge::image::color::format::rgba8,
					texture_parameters_.emulate_srgb()
				),
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
				_name
			)
			<< FCPPT_TEXT(", ")
			<< sge::cegui::from_cegui_size<
				sge::renderer::texture::planar::dim
			>(
				_size
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
	return
		*FCPPT_ASSERT_OPTIONAL_ERROR(
			texture_
		);
}

void
sge::cegui::texture::create_from_view(
	sge::image2d::view::const_object const &_view
)
{
	FCPPT_ASSERT_PRE(
		!texture_.has_value()
		&&
		!size_.has_value()
		&&
		!texel_scaling_.has_value()
	);

	CEGUI::Sizef const new_size(
		sge::cegui::to_cegui_size<
			CEGUI::Sizef::value_type
		>(
			sge::image2d::view::size(
				_view
			)
		)
	);

	size_ =
		sge::cegui::texture::optional_sizef(
			new_size
		);

	texel_scaling_ =
		sge::cegui::texture::optional_vector2f(
			sge::cegui::texel_scaling(
				new_size
			)
		);

	texture_ =
		optional_planar_unique_ptr(
			sge::renderer::texture::create_planar_from_view(
				texture_parameters_.renderer(),
				_view,
				sge::renderer::texture::mipmap::off(),
				sge::renderer::resource_flags_field::null(),
				texture_parameters_.emulate_srgb()
			)
		);
}

bool
sge::cegui::texture::empty() const
{
	return
		!texture_.has_value();
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
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			size_
		);
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
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			texel_scaling_
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
				_filename
			)
			<< FCPPT_TEXT(", ")
			<< sge::cegui::from_cegui_string(
				_resource_group
			)
			<< FCPPT_TEXT(')')
	);

	this->create_from_view(
		sge::image2d::load_exn(
			texture_parameters_.image_system(),
			sge::cegui::to_absolute_path(
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
		sge::cegui::from_cegui_size<
			sge::renderer::texture::planar::dim
		>(
			this->getSize()
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

	sge::renderer::texture::scoped_planar_lock const lock(
		this->impl(),
		sge::renderer::lock_mode::writeonly
	);

	sge::image2d::algorithm::copy_and_convert(
		sge::image2d::view::make_const(
			fcppt::cast::from_void_ptr<
				sge::image::const_raw_pointer
			>(
				_buffer
			),
			sge::cegui::from_cegui_size<
				sge::image2d::dim
			>(
				_buffer_size
			),
			FCPPT_ASSERT_OPTIONAL_ERROR(
				format
			),
			fcppt::math::dim::null<
				sge::image2d::pitch
			>()
		),
		lock.value(),
		sge::image::algorithm::may_overlap::no,
		sge::image::algorithm::uninitialized::yes
	);
}

void
sge::cegui::texture::blitFromMemory(
	void const *,
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
		).has_value();
}
