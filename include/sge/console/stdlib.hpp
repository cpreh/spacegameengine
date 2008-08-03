#ifndef SGE_CONSOLE_STDLIB_HPP_INCLUDED
#define SGE_CONSOLE_STDLIB_HPP_INCLUDED

#include "arg_list.hpp"
#include "../string.hpp"
#include <boost/function.hpp>

namespace sge
{
namespace con
{

struct stdlib
{
	typedef boost::function<void (const sge::string &)> callback_type;

	callback_type print;

	void set(const arg_list &);
	void get(const arg_list &);
	void help(const arg_list &);
	void listvars(const arg_list &);
	void listfuncs(const arg_list &);
	void latch(const arg_list &);

	explicit stdlib(const callback_type &);
};

}
}

#endif
