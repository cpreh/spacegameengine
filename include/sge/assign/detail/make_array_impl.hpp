#include <algorithm>

template<
	class T,
	std::size_t N>
sge::assign::detail::array<T,N>::array(
	T const &t)
{
	a[0] = t;
}

template<
	class T,
	std::size_t N>
sge::assign::detail::array<T,N>::array(
	array<T,N-1> const &that,
	T const &t)
{
	std::copy(
		that.a.begin(),
		that.a.end(),
		a.begin());

	a.back() = t;
}

template<
	class T,
	std::size_t N>
sge::assign::detail::array<T,N+1> 
sge::assign::detail::array<T,N>::operator()(
	T const &t)
{
	return array<T,N+1>(
		*this,
		t);
}

template<
	class T,
	std::size_t N>
sge::assign::detail::array<T,N>::operator container_type() const
{
	return a;
}

template<typename T>
sge::assign::detail::array<T,1> sge::assign::make_array(
	T const &t)
{
	return detail::array<T,1>(
		t);
}
