#ifndef SGE_SIGNAL_DETAIL_CONCRETE_CONNECTION_IMPL_HPP_INCLUDED
#define SGE_SIGNAL_DETAIL_CONCRETE_CONNECTION_IMPL_HPP_INCLUDED

template<typename T>
sge::signal::detail::concrete_connection<T>::concrete_connection(
	function_type const &_function)
	: function_(_function)
{
}

template<typename T>
typename sge::signal::detail::concrete_connection<T>::function_type &
	sge::signal::detail::concrete_connection<T>::function()
{
	return function_;
}

#endif
