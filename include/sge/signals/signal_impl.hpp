template<typename T>
sge::signals::auto_connection const sge::signals::signal<T>::connect(
	function_type const &_v)
{
	typedef detail::concrete_connection<T> impl_type;
	auto_connection c(
		new impl_type());
	connections_.push_back(
		*static_cast<impl_type *>(c.get()));
	return c;
}


