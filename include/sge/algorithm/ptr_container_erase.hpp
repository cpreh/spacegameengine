#ifndef SGE_ALGORITHM_PTR_CONTAINER_ERASE_HPP_INCLUDED
#define SGE_ALGORITHM_PTR_CONTAINER_ERASE_HPP_INCLUDED

namespace sge
{
namespace algorithm
{
template<
	typename Container,
	typename Ptr>
void ptr_container_erase(
	Container &,
	Ptr);
}
}

#include "detail/ptr_container_erase_impl.hpp"

#endif
