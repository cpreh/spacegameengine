#include <sge/gui/size_policy.hpp>

sge::gui::size_policy const sge::gui::size_policy::default_policy(
	axis_policy::type(axis_policy::can_grow) | axis_policy::can_shrink,
	axis_policy::type(axis_policy::can_grow) | axis_policy::can_shrink);

sge::gui::size_policy::size_policy(
	axis_policy::type const &x_,
	axis_policy::type const &y_)
	: x_(x_),
	  y_(y_) 
{}
