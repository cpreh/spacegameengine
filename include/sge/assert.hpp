#ifndef SGE_ASSERT_HPP_INCLUDED
#define SGE_ASSERT_HPP_INCLUDED

#include "string.hpp"
#include "text.hpp"
#include "export.hpp"
#include "stringize.hpp"
#include "file.hpp"

namespace sge
{
namespace detail
{
SGE_SYMBOL void process_assert(
	string const &file,
	string const &line,
	string const &condition,
	string const &message = string(),
	string const &function = string());
}
}

#define SGE_ASSERT_MESSAGE(cond,message)\
if (!(cond))\
	sge::detail::process_assert(\
		SGE_FILE,\
		SGE_STRINGIZE(__LINE__),\
		SGE_STRINGIZE(cond),\
		message);

#define SGE_ASSERT(cond)\
if (!(cond))\
	sge::detail::process_assert(\
		SGE_FILE,\
		SGE_STRINGIZE(__LINE__),\
		SGE_STRINGIZE(cond));

#endif
