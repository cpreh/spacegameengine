#ifndef SGE_ASSIGN_MAKE_ARRAY_HPP_INCLUDED
#define SGE_ASSIGN_MAKE_ARRAY_HPP_INCLUDED

#include <boost/tr1/array.hpp>
#include <cstddef>

namespace sge
{
namespace assign
{
namespace detail
{
template<
	class T,
	std::size_t N>
class array
{
public:
	typedef std::tr1::array<T,N> container_type;

	array(
		T const &);

	array(
		array<T,N-1> const &,
		T const &);
	
	array<T,N+1> operator()(T const &);

	operator container_type() const;
private:
	friend class array<T,N+1>;

	container_type a;
};
}

template<typename T>
detail::array<T,1> make_array(T const &);
}
}

#include <sge/assign/detail/make_array_impl.hpp>

#endif
