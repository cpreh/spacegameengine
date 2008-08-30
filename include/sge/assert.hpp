#ifndef SGE_ASSERT_HPP_INCLUDED
#define SGE_ASSERT_HPP_INCLUDED

#include "string.hpp"
#include "text.hpp"
#include "export.hpp"
#include <boost/preprocessor/stringize.hpp>

namespace sge
{
namespace detail
{

SGE_SYMBOL void process_assert(
	string const &file,
	string const &line,
	string const &condition,
	string const &message,
	string const &function = string());
}
}

#ifdef SGE_NARROW_STRING
#define SGE_ASSERT_MESSAGE(cond,message)\
if (!(cond))\
	sge::detail::process_assert(\
		__FILE__,\
		BOOST_PP_STRINGIZE(__LINE__),\
		#cond,\
		message);

#define SGE_ASSERT(cond)\
if (!(cond))\
	sge::detail::process_assert(\
		__FILE__,\
		BOOST_PP_STRINGIZE(__LINE__),\
		#cond,\
		BOOST_PP_STRINGIZE(message));
#else
#define SGE_ASSERT_MESSAGE(cond,message)\
if (!(cond))\
	sge::detail::process_assert(\
		SGE_TEXT(__FILE__),\
		BOOST_PP_STRINGIZE_W(__LINE__),\
		SGE_TEXT(#cond),\
		message);

#define SGE_ASSERT(cond)\
if (!(cond))\
	sge::detail::process_assert(\
		SGE_TEXT(__FILE__),\
		BOOST_PP_STRINGIZE_W(__LINE__),\
		SGE_TEXT(#cond),\
		BOOST_PP_STRINGIZE_W(message));
#endif

#endif
