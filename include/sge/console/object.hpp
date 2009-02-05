#ifndef SGE_CONSOLE_OBJECT_HPP_INCLUDED
#define SGE_CONSOLE_OBJECT_HPP_INCLUDED

#include <sge/console/callbacks.hpp>
#include <sge/console/var_map.hpp>
#include <sge/console/callback_map.hpp>
#include <sge/console/var_base_fwd.hpp>
#include <sge/signals/connection.hpp>
#include <sge/export.hpp>

#include <boost/noncopyable.hpp>

namespace sge
{
namespace console
{
class SGE_CLASS_SYMBOL object : public boost::noncopyable
{
	public:
	SGE_SYMBOL object(string::value_type prefix);
	
	SGE_SYMBOL signals::connection const insert(
		string const &name,
		callback const &,
		string const &description);

	SGE_SYMBOL signals::connection const register_fallback(
		fallback const &
	);
	
	SGE_SYMBOL void eval(string const &);
	SGE_SYMBOL var_map const &vars() const;
	SGE_SYMBOL callback_map const &functions() const;
	private:
	friend class var_base;
	
	var_map vars_;
	callback_map funcs_;
	fallback_signal fallback_;
	string::value_type prefix_;

	void insert(var_base &);
	void erase(var_base &);
};
}
}

#endif
