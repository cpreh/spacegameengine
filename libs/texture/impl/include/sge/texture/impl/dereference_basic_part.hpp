//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TEXTURE_IMPL_DEREFERENCE_BASIC_PART_HPP_INCLUDED
#define SGE_TEXTURE_IMPL_DEREFERENCE_BASIC_PART_HPP_INCLUDED

#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace texture
{
namespace impl
{

template<
	typename T
>
inline
T &
dereference_basic_part(
	T &_ref
)
{
	return
		_ref;
}

template<
	typename T
>
inline
T &
dereference_basic_part(
	fcppt::unique_ptr<
		T
	> const &_ptr
)
{
	return
		*_ptr;
}

}
}
}

#endif
