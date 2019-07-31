//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_STORE_VIEW_ANY_HPP_INCLUDED
#define SGE_IMAGE_IMPL_STORE_VIEW_ANY_HPP_INCLUDED

#include <fcppt/variant/apply.hpp>


namespace sge
{
namespace image
{
namespace impl
{
namespace store
{

template<
	typename Result,
	typename Store
>
Result
view_any(
	Store &_store
)
{
	return
		fcppt::variant::apply(
			[](
				auto &_store_inner
			)
			{
				return
					Result(
						_store_inner.wrapped_view()
					);
			},
			_store.get()
		);
}

}
}
}
}

#endif
