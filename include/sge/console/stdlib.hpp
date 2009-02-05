#ifndef SGE_CONSOLE_STDLIB_HPP_INCLUDED
#define SGE_CONSOLE_STDLIB_HPP_INCLUDED

#include "arg_list.hpp"
#include "../string.hpp"
#include "../export.hpp"
#include <boost/function.hpp>

namespace sge
{
namespace console
{

struct stdlib
{
	typedef boost::function<void (const sge::string &)> callback_type;

	callback_type print;

	SGE_SYMBOL void set(const arg_list &);
	SGE_SYMBOL void get(const arg_list &);
	SGE_SYMBOL void help(const arg_list &);
	SGE_SYMBOL void listvars(const arg_list &);
	SGE_SYMBOL void listfuncs(const arg_list &);
	SGE_SYMBOL void latch(const arg_list &);

	SGE_SYMBOL explicit stdlib(
		callback_type const &);
};

}
}

#endif
