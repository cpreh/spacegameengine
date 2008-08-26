#include <sge/gui/size_policy.hpp>

sge::gui::axis_policy::type const 
	sge::gui::size_policy::default_policy(axes_policy::preferred,axes_policy::preferred);

sge::gui::size_policy::size_policy(axis_policy::type const &x,axis_policy::type const &y)
	: x(x),y(y) {}
