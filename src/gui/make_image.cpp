#include <sge/gui/make_image.hpp>
#include <sge/gui/dim.hpp>
#include <sge/renderer/copy_and_convert_pixels.hpp>
#include <sge/renderer/image_view.hpp>
#include <sge/image/object.hpp>

sge::gui::image_ptr const sge::gui::make_image(
	sge::image::object_ptr _image)
{
	sge::gui::image_ptr i(
		new gui::image(
			_image->dim().w(),
			_image->dim().h()));

	renderer::copy_and_convert_pixels(
		_image->view(),
		renderer::image_view(boost::gil::view(*i)));
	
	return i;
}
