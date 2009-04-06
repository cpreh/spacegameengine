#ifndef SGE_CONSOLE_STDLIB_HPP_INCLUDED
#define SGE_CONSOLE_STDLIB_HPP_INCLUDED

#include <sge/console/object_fwd.hpp>
#include <sge/console/function_map.hpp>
#include <sge/signal/scoped_connection.hpp>
#include <sge/export.hpp>
#include <boost/function.hpp>

namespace sge
{
namespace console
{
class stdlib
{
public:
	typedef boost::function<void (string const &)> print_callback;
	typedef boost::function<void (string const &)> error_callback;
	SGE_SYMBOL stdlib(
		object &,
		print_callback const &,
		error_callback const &);
private:
	object &object_;
	print_callback print_;
	error_callback error_;
	// FIXME: connection_manager
	sge::signal::scoped_connection
		get,
		set,
		help,
		lsfuncs
		,lsvars,man;
	
	void fn_get(arg_list const &);
	void fn_set(arg_list const &);
	void fn_help(arg_list const &);
	void fn_lsvars(arg_list const &);
	void fn_man(arg_list const &);

	void print_function(function_map::const_reference);
};
}
}

#endif
