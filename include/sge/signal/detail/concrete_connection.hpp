#ifndef SGE_SIGNAL_DETAIL_CONCRETE_CONNECTION_HPP_INCLUDED
#define SGE_SIGNAL_DETAIL_CONCRETE_CONNECTION_HPP_INCLUDED

#include <sge/signal/detail/connection.hpp>
#include <boost/function.hpp>

namespace sge
{
namespace signal
{
namespace detail
{
template<typename T>
class concrete_connection : public connection
{
public:
	typedef T function_signature;
	typedef boost::function<T> function_type;

	concrete_connection(
		function_type const &);

	function_type &function();
private:
	function_type function_;
};
}
}
}

#endif
