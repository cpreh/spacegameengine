#include <sge/log/scoped_indent.hpp>
#include <sge/log/logger.hpp>
#include <sge/log/indent.hpp>
#include <sge/log/unindent.hpp>
#include <sge/log/temporary_output.hpp>

sge::log::scoped_indent::scoped_indent(
	logger &_logger,
	string const &_begin,
	string const &_end,
	level::type const _level)
: 
	logger_(_logger),
	end_(_end),
	level_(_level)
{
	logger_.log(
		level_,
		_1 << _begin << indent);
}

sge::log::scoped_indent::~scoped_indent()
{
	logger_.log(
		level_,
		_1 << unindent << end_);
}
