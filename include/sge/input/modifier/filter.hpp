#ifndef SGE_INPUT_MODIFIER_FILTER_HPP_INCLUDED
#define SGE_INPUT_MODIFIER_FILTER_HPP_INCLUDED

#include <sge/input/modifier/states.hpp>
#include <sge/export.hpp>
#include <sge/input/key_pair_fwd.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/signals/connection.hpp>
#include <sge/signals/scoped_connection.hpp>
#include <sge/signals/signal.hpp>
#include <boost/function.hpp>

namespace sge
{
namespace input
{
namespace modifier
{
class SGE_CLASS_SYMBOL filter
{
	public:
	typedef void fn_callback_type (key_pair const &,states const &);
	typedef boost::function<fn_callback_type> callback_type;
	typedef void fn_repeat_callback_type (key_type const &,states const &);
	typedef boost::function<fn_repeat_callback_type> repeat_callback_type;

	SGE_SYMBOL explicit filter(system_ptr);

	SGE_SYMBOL signals::connection const register_callback(
		callback_type const &);
	SGE_SYMBOL signals::connection const register_repeat_callback(
		repeat_callback_type const &);
	private:
	signals::signal<fn_callback_type> signal;
	signals::signal<fn_repeat_callback_type> repeat_signal;
	signals::scoped_connection ic,irc;
	states modifiers;

	void input_callback(key_pair const &);
	void input_repeat_callback(key_type const &);
};
}
}
}

#endif
