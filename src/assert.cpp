#include <sge/assert.hpp>
#include <sge/exception.hpp>
#include <sge/iostream.hpp>
#include <sge/sstream.hpp>
#include <ostream>

void sge::detail::process_assert(
	string const &file,
	string const &line,
	string const &condition,
	string const &message,
	string const &function)
{
	ostringstream ss;
	
	ss << file << SGE_TEXT(':') << line;
	
	if (!function.empty())
		ss << SGE_TEXT(" function '") << function << SGE_TEXT('\'');
	ss << SGE_TEXT(": assertion failed: ") << condition;
	
	if (!message.empty())
		ss << SGE_TEXT(", ") << message;

	cerr << ss.str() << SGE_TEXT('\n');
	throw exception(ss.str());
}
