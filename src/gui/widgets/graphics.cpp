#include <sge/gui/widgets/graphics.hpp>
#include <sge/gui/widgets/parameters.hpp>
#include <sge/image/object.hpp>
#include <sge/gui/image.hpp>
#include <sge/structure_cast.hpp>

sge::gui::widgets::graphics::graphics(
	widgets::parent_data const &_parent,
	widgets::parameters _params,
	const_image_ptr const _image)
: 
	base(
		_parent,
		_params
			.size_policy(
				sge::gui::size_policy(
					axis_policy::none,
					axis_policy::none)))
{
	buffer() = *_image;
}
