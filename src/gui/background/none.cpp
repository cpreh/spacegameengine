#include <sge/gui/background/base.hpp>
#include <sge/gui/background/none.hpp>
#include <sge/gui/main_area/base_fwd.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/rect.hpp>


sge::gui::background::none::none(
	sge::gui::main_area::base &_main_area
)
:
	sge::gui::background::base(
		_main_area
	)
{
}

sge::gui::background::none::~none()
{
}

void
sge::gui::background::none::on_draw(
	sge::gui::renderer::base &,
	sge::renderer::context::ffp &,
	sge::rucksack::rect
)
{
}
