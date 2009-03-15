#ifndef SGE_CONSOLE_OBJECT_HPP_INCLUDED
#define SGE_CONSOLE_OBJECT_HPP_INCLUDED

#include <sge/console/callbacks.hpp>
#include <sge/console/variable_map.hpp>
#include <sge/console/function_map.hpp>
#include <sge/console/var_base_fwd.hpp>
#include <sge/signal/auto_connection.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace console
{
class SGE_CLASS_SYMBOL object
{
	SGE_NONCOPYABLE(object)
	public:
	SGE_SYMBOL explicit object(string::value_type prefix);
	
	SGE_SYMBOL sge::signal::auto_connection insert(
		string const &name,
		callback const &,
		string const &description = string());

	SGE_SYMBOL sge::signal::auto_connection register_fallback(
		fallback const &
	);
	
	SGE_SYMBOL void eval(string const &);
	SGE_SYMBOL variable_map const &variables() const;
	SGE_SYMBOL variable_map &variables();
	SGE_SYMBOL function_map const &functions() const;
	private:
	friend class var_base;
	
	variable_map vars_;
	function_map funcs_;
	fallback_signal fallback_;
	string::value_type prefix_;

	void insert(var_base &);
	void erase(var_base &);
};
}
}

#endif
