#include <sge/gui/main_area/base.hpp>
#include <sge/gui/main_area/viewport_adaptor.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>


sge::gui::main_area::viewport_adaptor::viewport_adaptor(
	sge::renderer::device::core &_device,
	sge::viewport::manager &_viewport_manager,
	sge::gui::widget::base &_widget
)
:
	sge::gui::main_area::base(),
	widget_(
		_widget
	),
	impl_(
		_viewport_manager,
		_device
	)
{
	impl_.child(
		_widget.layout()
	);

	impl_.relayout();
}

sge::gui::main_area::viewport_adaptor::~viewport_adaptor()
{
}

void
sge::gui::main_area::viewport_adaptor::relayout()
{
	impl_.relayout();
}

sge::gui::widget::base &
sge::gui::main_area::viewport_adaptor::widget()
{
	return
		widget_;
}
