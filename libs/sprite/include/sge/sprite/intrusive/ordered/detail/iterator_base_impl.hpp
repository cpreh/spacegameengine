//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_INTRUSIVE_ORDERED_DETAIL_ITERATOR_BASE_IMPL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_ORDERED_DETAIL_ITERATOR_BASE_IMPL_HPP_INCLUDED

#include <sge/sprite/intrusive/ordered/iterator_fwd.hpp>
#include <sge/sprite/intrusive/ordered/detail/range_iterator.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <iterator>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace intrusive
{
namespace ordered
{
namespace detail
{

template<
	typename Choices,
	typename Order,
	bool IsConst
>
struct iterator_base_impl
{
	typedef
	std::iterator_traits<
		sge::sprite::intrusive::ordered::detail::range_iterator<
			Choices,
			IsConst
		>
	>
	range_iterator_traits;

	typedef
	boost::iterator_facade<
		sge::sprite::intrusive::ordered::iterator<
			Choices,
			Order,
			IsConst
		>,
		typename
		range_iterator_traits::value_type,
		std::forward_iterator_tag,
		typename
		range_iterator_traits::reference,
		typename
		range_iterator_traits::difference_type
	>
	type;
};

}
}
}
}
}

#endif
