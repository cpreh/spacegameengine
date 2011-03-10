#include <sge/cegui/logger.hpp>
#include <sge/log/global_context.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/parameters/root.hpp>
#include <fcppt/log/parameters/all.hpp>
#include <fcppt/io/clog.hpp>
#include <fcppt/text.hpp>

fcppt::log::object &
sge::cegui::logger()
{
	static fcppt::log::object global_(
		fcppt::log::parameters::root(
			fcppt::io::clog)
		.prefix(
			FCPPT_TEXT("sgegui"))
		.enabled(
			true)
		.level(
			fcppt::log::level::warning)
		.context(
			sge::log::global_context())
		.create());

	return global_;
}
