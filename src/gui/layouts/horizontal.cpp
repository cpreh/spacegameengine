#include <sge/gui/layouts/horizontal.hpp>
#include <sge/gui/widgets/container.hpp>
#include <sge/iostream.hpp>

sge::gui::layouts::horizontal::horizontal(widgets::container &w)
	: row(w)
{
	sge::cerr << "horizontal: constructed horizontal layout\n";
}
