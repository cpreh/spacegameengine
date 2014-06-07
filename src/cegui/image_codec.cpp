/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/image2d/file.hpp>
#include <sge/image2d/load_raw_exn.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/optional_extension.hpp>
#include <sge/src/cegui/image_codec.hpp>
#include <sge/src/cegui/texture.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/ImageCodec.h>
#include <CEGUI/Texture.h>
#include <fcppt/config/external_end.hpp>


sge::cegui::image_codec::image_codec(
	sge::image2d::system &_image_system
)
:
	CEGUI::ImageCodec(
		"sge image codec"
	),
	image_system_(
		_image_system
	)
{
}

sge::cegui::image_codec::~image_codec()
{
}

CEGUI::Texture *
sge::cegui::image_codec::load(
	CEGUI::RawDataContainer const &_data,
	CEGUI::Texture *const _result_texture
)
{
	FCPPT_ASSERT_PRE(
		_result_texture
	);

	dynamic_cast<
		sge::cegui::texture &
	>(
		*_result_texture
	).create_from_view(
		sge::image2d::load_raw_exn(
			image_system_,
			sge::media::const_raw_range(
				_data.getDataPtr(),
				_data.getDataPtr() + _data.getSize()
			),
			sge::media::optional_extension()
		)
		->view()
	);

	return _result_texture;
}

sge::image2d::system &
sge::cegui::image_codec::image_system() const
{
	return image_system_;
}
