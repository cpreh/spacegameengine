#ifndef SGE_LOG_SCOPED_INDENT_HPP_INCLUDED
#define SGE_LOG_SCOPED_INDENT_HPP_INCLUDED

#include <sge/log/logger_fwd.hpp>
#include <sge/log/level.hpp>
#include <sge/string.hpp>

namespace sge
{
namespace log
{
class scoped_indent
{
public:
	scoped_indent(
		logger &,
		string const &,
		string const &,
		level::type = level::debug);
	~scoped_indent();
private:
	logger &logger_;
	string const end_;
	level::type const level_;
};
}
}

#endif
