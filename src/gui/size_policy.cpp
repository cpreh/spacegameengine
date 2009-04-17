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

sge::gui::axis_policy::type const &sge::gui::size_policy::x() const 
{ 
	return x_; 
}

sge::gui::axis_policy::type const &sge::gui::size_policy::y() const 
{ 
	return y_; 
}

// this is a hack so we can use it with the layouts::row::master stuff
sge::gui::axis_policy::type const &sge::gui::size_policy::index(
	std::size_t const i) const
{ 
	return i == static_cast<std::size_t>(0) ? x() : y(); 
}
