//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cegui/impl/image_codec.hpp>
#include <sge/cegui/impl/texture.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/load_raw_exn.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/optional_extension.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/ImageCodec.h>
#include <CEGUI/Texture.h>
#include <fcppt/config/external_end.hpp>


sge::cegui::impl::image_codec::image_codec(
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

sge::cegui::impl::image_codec::~image_codec()
{
}

CEGUI::Texture *
sge::cegui::impl::image_codec::load(
	CEGUI::RawDataContainer const &_data,
	CEGUI::Texture *const _result_texture
)
{
	FCPPT_ASSERT_PRE(
		_result_texture
	);

	dynamic_cast<
		sge::cegui::impl::texture &
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
sge::cegui::impl::image_codec::image_system() const
{
	return image_system_;
}
