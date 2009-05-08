#ifndef SGE_LOG_SCOPED_INDENT_HPP_INCLUDED
#define SGE_LOG_SCOPED_INDENT_HPP_INCLUDED

#include <sge/log/logger_fwd.hpp>
#include <sge/log/level.hpp>
#include <sge/string.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace log
{
class SGE_CLASS_SYMBOL scoped_indent
{
SGE_NONCOPYABLE(scoped_indent)
public:
	SGE_SYMBOL scoped_indent(
		logger &,
		string const &,
		string const &,
		level::type = level::debug);
	SGE_SYMBOL ~scoped_indent();
private:
	logger &logger_;
	string const end_;
	level::type const level_;
};
}
}

#endif
