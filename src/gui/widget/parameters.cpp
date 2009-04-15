#include <sge/gui/widget.hpp>

sge::gui::widget::parameters::parameters()
: 
	pos_(point::null()),
	size_(),
	size_policy_(size_policy_t::default_policy),
	keyboard_focus_(keyboard_focus::ignore),
	activation_(activation_state::active)
{
}

sge::gui::widget::parameters &
sge::gui::widget::parameters::pos(
	point const &_pos) 
{ 
	pos_ = _pos; 
	return *this; 
}

sge::gui::widget::parameters &
sge::gui::widget::parameters::size(
	dim const &_size) 
{ 
	size_ = _size; 
	return *this; 
}

sge::gui::widget::parameters &
sge::gui::widget::parameters::size_policy(
	size_policy_t const &_size_policy) 
{ 
	size_policy_ = _size_policy; 
	return *this; 
}

sge::gui::widget::parameters &
sge::gui::widget::parameters::keyboard_focus(
	keyboard_focus::type const &_keyboard_focus) 
{ 
	keyboard_focus_ = _keyboard_focus; 
	return *this; 
}

sge::gui::widget::parameters &
sge::gui::widget::parameters::layout(
	layout_auto_ptr _layout) 
{ 
	layout_ = _layout; 
	return *this; 
}

sge::gui::widget::parameters &
sge::gui::widget::parameters::activation(
	activation_state::type const _activation) 
{ 
	activation_ = _activation; 
	return *this; 
}

sge::gui::point const &sge::gui::widget::parameters::pos() const
{
	return pos_;
}

boost::optional<sge::gui::dim> const &sge::gui::widget::parameters::size() const
{
	return size_;
}

sge::gui::widget::size_policy_t const &sge::gui::widget::parameters::size_policy() const
{
	return size_policy_;
}

sge::gui::keyboard_focus::type const &sge::gui::widget::parameters::keyboard_focus() const
{
	return keyboard_focus_;
}

sge::gui::layout_auto_ptr sge::gui::widget::parameters::layout() const
{
	return layout_;
}

sge::gui::activation_state::type sge::gui::widget::parameters::activation() const
{
	return activation_;
}
