#include <sge/gui/layouts/horizontal.hpp>

sge::gui::layouts::horizontal::horizontal()
	: row()
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
