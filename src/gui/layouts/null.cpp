#include <sge/gui/layouts/null.hpp>
#include <sge/gui/widget.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/log.hpp>

namespace
{
sge::gui::logger mylogger(sge::gui::global_log(),SGE_TEXT("layouts::null"),false);
}

sge::gui::layouts::null::null(widget &w)
	: layout(w)
{
}

void sge::gui::layouts::null::update()
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("in update, doing nothing"));
}

void sge::gui::layouts::null::pos(point const &p)
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("in update, setting position"));
	layout::set_widget_pos(connected_widget(),p);
}

void sge::gui::layouts::null::size(dim const &p)
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("in update, setting size"));
	layout::set_widget_size(connected_widget(),p);
}

sge::gui::dim const sge::gui::layouts::null::size_hint() const
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("getting size hint from skin"));
	return connected_widget().parent_manager().skin().size_hint(
		connected_widget());
}
