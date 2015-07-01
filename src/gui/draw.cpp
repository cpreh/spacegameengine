#include <sge/gui/draw.hpp>
#include <sge/gui/background/base.hpp>
#include <sge/gui/main_area/base.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>


void
sge::gui::draw(
	sge::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context,
	sge::gui::background::base &_background,
	sge::gui::main_area::base &_main_area
)
{
	_background.draw(
		_renderer,
		_context
	);

	_main_area.widget().on_draw(
		_renderer,
		_context
	);
}
