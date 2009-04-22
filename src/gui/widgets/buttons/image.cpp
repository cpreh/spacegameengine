#include <sge/gui/widgets/buttons/image.hpp>
#include <sge/gui/widgets/parameters.hpp>
#include <sge/assert.hpp>

sge::gui::widgets::buttons::image::image(
	parent_data const &_parent,
	parameters _params,
	const_image_ptr _normal,
	const_image_ptr _hover,
	const_image_ptr _keyboard,
	const_image_ptr _hover_keyboard)
:
	base(
		_parent,
		_params
			.size_policy(
				sge::gui::size_policy(
					axis_policy::none,
					axis_policy::none))
				/*
				.size(
					dim(
						static_cast<unit>(normal_->width()),
						static_cast<unit>(normal_->height())))*/),
	normal_(_normal),
	hover_(_hover),
	keyboard_(_keyboard),
	hover_keyboard_(_hover_keyboard)
{
	SGE_ASSERT(
		normal_->size() == hover_->size() && 
		hover_->size() == keyboard_->size() && 
		keyboard_->size() == hover_keyboard_->size());
}
