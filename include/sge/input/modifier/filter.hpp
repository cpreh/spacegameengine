#ifndef SGE_INPUT_MODIFIER_FILTER_HPP_INCLUDED
#define SGE_INPUT_MODIFIER_FILTER_HPP_INCLUDED

#include "states.hpp"
#include "../../export.hpp"
#include "../key_pair_fwd.hpp"
#include "../system_fwd.hpp"
#include "../../signals/scoped_connection.hpp"
#include "../../signals/signal.hpp"
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

	SGE_SYMBOL explicit filter(system_ptr);

	SGE_SYMBOL signals::scoped_connection const register_callback(
		callback_type const &);
	private:
	signals::signal<fn_callback_type> signal;
	states modifiers;

	void input_callback(key_pair const &);
};
}
}
}

#endif
