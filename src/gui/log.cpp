#include <sge/gui/log.hpp>
#include <sge/log/global.hpp>
#include <sge/text.hpp>

sge::log::logger &sge::gui::global_log()
{
	static logger global(
		sge::log::global(),
		SGE_TEXT("gui"),
		log::level::debug
	);

	return global;
}

sge::gui::logger::logger(
	log::logger &parent,
	string const &prefix,
	bool const active)
:
	sge::log::logger(
		parent,
		prefix + SGE_TEXT(": "),
		active
	)
{
}
