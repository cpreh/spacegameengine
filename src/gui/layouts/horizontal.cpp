#include <sge/gui/layouts/horizontal.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/vector/basic_impl.hpp>

sge::gui::layouts::horizontal::horizontal(
	widget &w)
:
	row(w)
{
}

sge::gui::dim::reference sge::gui::layouts::horizontal::master(
	dim &d) const
{
	return d.w();
}

sge::gui::dim::const_reference sge::gui::layouts::horizontal::master(
	dim const &d) const
{
	return d.w();
}

sge::gui::point::reference sge::gui::layouts::horizontal::master(
	point &d) const
{
	return d.x();
}

sge::gui::point::const_reference sge::gui::layouts::horizontal::master(
	point const &d) const
{
	return d.x();
}
