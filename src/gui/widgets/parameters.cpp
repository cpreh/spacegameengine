#include <sge/gui/widgets/parameters.hpp>

sge::gui::widgets::parameters::parameters()
: 
	pos_(point::null()),
	size_(),
	size_policy_(sge::gui::size_policy::default_policy),
	keyboard_focus_(keyboard_focus::ignore),
	activation_(activation_state::active)
{
}

sge::gui::widgets::parameters &
sge::gui::widgets::parameters::pos(
	point const &_pos) 
{ 
	pos_ = _pos; 
	return *this; 
}

sge::gui::widgets::parameters &
sge::gui::widgets::parameters::size(
	dim const &_size) 
{ 
	size_ = _size; 
	return *this; 
}

sge::gui::widgets::parameters &
sge::gui::widgets::parameters::size_policy(
	sge::gui::size_policy const &_size_policy) 
{ 
	size_policy_ = _size_policy; 
	return *this; 
}

sge::gui::widgets::parameters &
sge::gui::widgets::parameters::keyboard_focus(
	keyboard_focus::type const &_keyboard_focus) 
{ 
	keyboard_focus_ = _keyboard_focus; 
	return *this; 
}

sge::gui::widgets::parameters &
sge::gui::widgets::parameters::layout(
	layouts::auto_ptr _layout) 
{ 
	layout_ = _layout; 
	return *this; 
}

sge::gui::widgets::parameters &
sge::gui::widgets::parameters::activation(
	activation_state::type const _activation) 
{ 
	activation_ = _activation; 
	return *this; 
}

sge::gui::point const &sge::gui::widgets::parameters::pos() const
{
	return pos_;
}

boost::optional<sge::gui::dim> const &sge::gui::widgets::parameters::size() const
{
	return size_;
}

sge::gui::size_policy const &sge::gui::widgets::parameters::size_policy() const
{
	return size_policy_;
}

sge::gui::keyboard_focus::type const &sge::gui::widgets::parameters::keyboard_focus() const
{
	return keyboard_focus_;
}

sge::gui::layouts::auto_ptr sge::gui::widgets::parameters::layout() const
{
	return layout_;
}

sge::gui::activation_state::type sge::gui::widgets::parameters::activation() const
{
	return activation_;
}
