#include <sge/gui/widgets/graphics.hpp>
#include <sge/image/object.hpp>
#include <sge/structure_cast.hpp>

sge::gui::widgets::graphics::graphics(
	widget::parent_data const &_parent,
	widget::parameters _params,
	const_image_ptr const _image)
	: widget(
			_parent,
			_params
				.size_policy(
					size_policy_t(
						axis_policy::none,
						axis_policy::none)))
{
	buffer() = *_image;
}
