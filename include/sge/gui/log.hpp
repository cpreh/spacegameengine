#ifndef SGE_GUI_LOG_HPP_INCLUDED
#define SGE_GUI_LOG_HPP_INCLUDED

#include "../log/logger.hpp"
#include "../log/level.hpp"
#include "../log/macros.hpp"
#include "../log/temporary_output.hpp"

namespace sge
{
namespace gui
{
class logger : public sge::log::logger
{
	public:
	logger(sge::log::logger &parent,string const &prefix,bool = true);
};

sge::log::logger &global_log();
}
}

#endif
