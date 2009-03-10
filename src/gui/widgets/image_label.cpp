#include "../utility/to_internal_image.hpp"
#include <sge/gui/widgets/image_label.hpp>
#include <sge/image/object.hpp>
#include <sge/structure_cast.hpp>

sge::gui::widgets::image_label::image_label(
	widget::parent_data const &_parent,
	widget::parameters _params,
	const_image_ptr const _image)
	: widget(
			_parent,
			_params
				.size_policy(
					size_policy_t(
						axis_policy::none,
						axis_policy::none))
				.size(
					dim(
						static_cast<unit>(
							_image->width()),
						static_cast<unit>(
							_image->height()))))
{
	buffer() = *_image;
}
