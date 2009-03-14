template<typename T>
sge::signals::detail::concrete_connection<T>::concrete_connection(
	function_type const &_function)
	: function_(_function)
{
}

template<typename T>
typename sge::signals::detail::concrete_connection<T>::function_type &
	sge::signals::detail::concrete_connection<T>::function()
{
	return function_;
}
