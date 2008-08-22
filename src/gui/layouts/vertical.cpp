#include <sge/gui/layouts/vertical.hpp>
#include <sge/gui/widgets/container.hpp>
#include <sge/iostream.hpp>

sge::gui::layouts::vertical::vertical(widgets::container &w)
	: row(w)
{
	sge::cerr << "vertical: constructed vertical layout\n";
}
