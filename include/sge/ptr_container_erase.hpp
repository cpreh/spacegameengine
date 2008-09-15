#ifndef PTR_CONTAINER_ERASE_HPP_INCLUDED
#define PTR_CONTAINER_ERASE_HPP_INCLUDED

#include <boost/lambda/lambda.hpp>

namespace sge
{
template<typename T,typename U>
void ptr_container_erase(T &container,U const ptr)
{
	container.erase_if(&boost::lambda::_1 == boost::lambda::constant(ptr));
}
}

#endif
