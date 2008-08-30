#ifndef SGE_ASSERT_HPP_INCLUDED
#define SGE_ASSERT_HPP_INCLUDED

#include "string.hpp"
#include "text.hpp"
#include "export.hpp"
#include <boost/preprocessor/stringize.hpp>
#include <boost/lexical_cast.hpp>

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
    SGE_TEXT(""));
#else
#define SGE_ASSERT_MESSAGE(cond,message)\
if (!(cond))\
	sge::detail::process_assert(\
		boost::lexical_cast<sge::string>(__FILE__),\
		boost::lexical_cast<sge::string>(__LINE__),\
		SGE_TEXT(#cond),\
		message);

#define SGE_ASSERT(cond)\
if (!(cond))\
	sge::detail::process_assert(\
    boost::lexical_cast<sge::string>(__FILE__),\
    boost::lexical_cast<sge::string>(__LINE__),\
    SGE_TEXT(#cond),\
		SGE_TEXT(""));
#endif

#endif
