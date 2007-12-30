#ifndef STDLIB_HPP_INCLUDED
#define STDLIB_HPP_INCLUDED

#include <boost/function.hpp>
#include "console.hpp"

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
	void listvars(const arg_list &);
	void listfuncs(const arg_list &);

	stdlib(const callback_type &);
};

}
}

#endif
