#include <sge/cegui/detail/image_codec.hpp>
#include <sge/cegui/detail/texture.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <sge/image2d/file_ptr.hpp>
#include <sge/optional_extension.hpp>
#include <sge/const_raw_range.hpp>
#include <sge/image2d/file.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/optional_impl.hpp>

sge::cegui::detail::image_codec::image_codec(
	sge::image2d::multi_loader &_image_loader)
:
	CEGUI::ImageCodec(
		"sge image codec"),
	image_loader_(
		_image_loader)
{
}

CEGUI::Texture *
sge::cegui::detail::image_codec::load(
	CEGUI::RawDataContainer const &data,
	CEGUI::Texture *result_texture)
{
	FCPPT_ASSERT(
		result_texture);

	dynamic_cast<texture &>(*result_texture).create_from_view(
		image_loader_.load(
			sge::const_raw_range(
				data.getDataPtr(),
				data.getDataPtr() + data.getSize()),
			sge::optional_extension())->view());

	return result_texture;
}

sge::image2d::multi_loader &
sge::cegui::detail::image_codec::loader() const
{
	return image_loader_;
}
