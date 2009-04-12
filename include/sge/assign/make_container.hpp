#ifndef SGE_ASSIGN_MAKE_CONTAINER_HPP_INCLUDED
#define SGE_ASSIGN_MAKE_CONTAINER_HPP_INCLUDED

namespace sge
{
namespace assign
{
template<typename Container>
class make_container
{
public:
	typedef Container container_type;

	make_container(
		typename container_type::const_reference);
	
	make_container &operator()(
		typename container_type::const_reference);
	
	operator Container() const;
private:
	container_type c_;
};
}
}

#include <sge/assign/detail/make_container_impl.hpp>

#endif
