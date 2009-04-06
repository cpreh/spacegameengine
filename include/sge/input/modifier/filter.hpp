#ifndef SGE_INPUT_MODIFIER_FILTER_HPP_INCLUDED
#define SGE_INPUT_MODIFIER_FILTER_HPP_INCLUDED

#include <sge/input/modifier/states.hpp>
#include <sge/container/map_decl.hpp>
#include <sge/input/key_pair_fwd.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/signal/auto_connection.hpp>
#include <sge/signal/scoped_connection.hpp>
#include <sge/signal/object.hpp>
#include <sge/noncopyable.hpp>
#include <sge/export.hpp>
#include <boost/function.hpp>

namespace sge
{
namespace input
{
namespace modifier
{
class SGE_CLASS_SYMBOL filter
{
	SGE_NONCOPYABLE(filter)
	public:
	typedef void fn_callback_type (key_pair const &,states const &);
	typedef boost::function<fn_callback_type> callback_type;
	typedef void fn_repeat_callback_type (key_type const &,states const &);
	typedef boost::function<fn_repeat_callback_type> repeat_callback_type;

	SGE_SYMBOL explicit filter(system_ptr);

	SGE_SYMBOL signal::auto_connection register_callback(
		callback_type const &);
	SGE_SYMBOL signal::auto_connection register_repeat_callback(
		repeat_callback_type const &);

	SGE_SYMBOL ~filter();
	private:
	signal::object<fn_callback_type> signal;
	signal::object<fn_repeat_callback_type> repeat_signal;
	signal::scoped_connection const ic, irc;
	states modifiers;

	void input_callback(key_pair const &);
	void input_repeat_callback(key_type const &);
};
}
}
}

#endif
