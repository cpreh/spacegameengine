#ifndef SGE_GUI_LOG_HPP_INCLUDED
#define SGE_GUI_LOG_HPP_INCLUDED

#include <sge/log/logger.hpp>
#include <sge/log/level.hpp>
#include <sge/log/macros.hpp>
#include <sge/log/temporary_output.hpp>

namespace sge
{
namespace gui
{
class logger : public sge::log::logger
{
	public:
	logger(
		sge::log::logger &parent,
		string const &prefix,
		bool active = true);
};

sge::log::logger &global_log();
}
}

#endif
