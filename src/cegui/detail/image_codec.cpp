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


#include <sge/cegui/detail/image_codec.hpp>
#include <sge/cegui/detail/texture.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/optional_extension.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/assert/pre.hpp>


sge::cegui::detail::image_codec::image_codec(
	sge::image2d::system &_image_system)
:
	CEGUI::ImageCodec(
		"sge image codec"),
	image_system_(
		_image_system)
{
}

sge::cegui::detail::image_codec::~image_codec()
{
}

CEGUI::Texture *
sge::cegui::detail::image_codec::load(
	CEGUI::RawDataContainer const &data,
	CEGUI::Texture *result_texture)
{
	FCPPT_ASSERT_PRE(
		result_texture);

	dynamic_cast<
		sge::cegui::detail::texture &
	>(
		*result_texture
	).create_from_view(
		image_system_.load_raw(
			sge::media::const_raw_range(
				data.getDataPtr(),
				data.getDataPtr() + data.getSize()
			),
			sge::media::optional_extension()
		)
		->view()
	);

	return result_texture;
}

sge::image2d::system &
sge::cegui::detail::image_codec::image_system() const
{
	return image_system_;
}
