#include <sge/gui/widgets/buttons/image.hpp>
#include <sge/assert.hpp>

sge::gui::widgets::buttons::image::image(
	parent_data const &_parent,
	parameters _params,
	const_image_ptr _normal,
	const_image_ptr _hover,
	const_image_ptr _keyboard,
	const_image_ptr _hover_keyboard)
	: base(
			_parent,
			_params
				.size_policy(
					size_policy_t(
						axis_policy::none,
						axis_policy::none))
				.size(
					dim(
						static_cast<unit>(normal_->width()),
						static_cast<unit>(normal_->height())))),
		normal_(_normal),
		hover_(_hover),
		keyboard_(_keyboard)
		hover_keyboard_(_hover_keyboard)
{
	SGE_ASSERT(
		normal_->dimensions() == hover_->dimensions() && 
		hover_->dimensions() == keyboard_->dimensions() && 
		keyboard_->dimensions() == hover_keyboard_->dimensions());
}
