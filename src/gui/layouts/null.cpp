#include <sge/gui/layouts/null.hpp>
#include <sge/gui/widgets/base.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/log.hpp>

namespace
{
sge::gui::logger mylogger(
	sge::gui::global_log(),
	SGE_TEXT("layouts::null"),
	false);
}

sge::gui::layouts::null::null()
: 
	base()
{
}

void sge::gui::layouts::null::compile(
	invalidation::type const &)
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("in compile, doing nothing"));
}

void sge::gui::layouts::null::compile_static()
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("in compile_static, doing nothing"));
}

sge::gui::dim const sge::gui::layouts::null::optimal_size() const
{
	SGE_LOG_DEBUG(
		mylogger,
		log::_1 << SGE_TEXT("getting size hint from skin"));
	return connected_widget().parent_manager().skin().optimal_size(
		connected_widget());
}
