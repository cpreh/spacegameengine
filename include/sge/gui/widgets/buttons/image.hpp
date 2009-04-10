#ifndef SGE_GUI_WIDGETS_BUTTONS_IMAGE_HPP_INCLUDED
#define SGE_GUI_WIDGETS_BUTTONS_IMAGE_HPP_INCLUDED

#include <sge/gui/widgets/buttons/base.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
namespace buttons
{
class SGE_CLASS_SYMBOL image : public base
{
public:
	SGE_GUI_SYMBOL image(
		parent_data const &,
		parameters,
		const_image_ptr normal,
		const_image_ptr hover,
		const_image_ptr keyboard,
		const_image_ptr hover_keyboard);
	
	// TODO: move to cpp file
	const_image_ptr normal() const { return normal_; }
	const_image_ptr hover() const { return hover_; }
	const_image_ptr keyboard() const { return keyboard_; }
	const_image_ptr hover_keyboard() const { return hover_keyboard_; }
private:
	const_image_ptr normal_,hover_,keyboard_,hover_keyboard_;
};
}
}
}
}

#endif
