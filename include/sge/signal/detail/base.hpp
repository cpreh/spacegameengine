#ifndef SGE_SIGNAL_DETAIL_BASE_HPP_INCLUDED
#define SGE_SIGNAL_DETAIL_BASE_HPP_INCLUDED

#include <sge/signal/detail/concrete_connection.hpp>
#include <sge/signal/auto_connection.hpp>
#include <sge/noncopyable.hpp>
#include <boost/intrusive/list.hpp>
#include <boost/function.hpp>

namespace sge
{
namespace signal
{
namespace detail
{
template<typename T>
class base
{
	SGE_NONCOPYABLE(base)
public:
	typedef T function_signature;
	typedef boost::function<T> function_type;
	typedef detail::concrete_connection<
			function_signature
		> concrete_connection;

	auto_connection connect(function_type const &f);
protected:
	typedef boost::intrusive::list<
		concrete_connection,
		boost::intrusive::constant_time_size<
			false
		>
	> connection_list;

	base();
	connection_list &connections();
private:
	connection_list connections_;
};
}
}
}

#endif
