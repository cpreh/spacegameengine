#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/dummy.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>


sge::gui::widget::dummy::dummy()
:
	sge::gui::widget::base()
{
}

sge::gui::widget::dummy::~dummy()
{
}

void
sge::gui::widget::dummy::on_draw(
	sge::gui::renderer::base &,
	sge::renderer::context::ffp &
)
{
}
