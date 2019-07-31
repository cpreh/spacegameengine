//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_INTRUSIVE_ORDERED_ITERATOR_DECL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_ORDERED_ITERATOR_DECL_HPP_INCLUDED

#include <sge/sprite/intrusive/ordered/iterator_fwd.hpp>
#include <sge/sprite/intrusive/ordered/detail/iterator_base.hpp>
#include <sge/sprite/intrusive/ordered/detail/iterator_empty.hpp>
#include <sge/sprite/intrusive/ordered/detail/map.hpp>
#include <sge/sprite/intrusive/ordered/detail/range_iterator.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/iterator_facade.hpp>
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

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Choices,
	typename Order,
	bool IsConst
>
class iterator final
:
	public sge::sprite::intrusive::ordered::detail::iterator_base<
		Choices,
		Order,
		IsConst
	>
{
	typedef
	sge::sprite::intrusive::ordered::detail::iterator_base<
		Choices,
		Order,
		IsConst
	>
	base;

	typedef
	sge::sprite::intrusive::ordered::detail::map<
		Order,
		Choices
	>
	ordered_map;

	typedef
	typename
	std::conditional<
		IsConst,
		typename
		ordered_map::const_iterator,
		typename
		ordered_map::iterator
	>::type
	ordered_map_iterator;
public:
	typedef
	typename
	base::value_type
	value_type;

	typedef
	typename
	base::reference
	reference;

	typedef
	typename
	base::pointer
	pointer;

	typedef
	typename
	base::difference_type
	difference_type;

	typedef
	typename
	base::iterator_category
	iterator_category;

	iterator(
		ordered_map_iterator current,
		ordered_map_iterator end
	);
private:
	friend class boost::iterator_core_access;

	void
	increment();

	reference
	dereference() const;

	bool
	equal(
		iterator const &
	) const;

	bool
	is_end() const;

	typedef
	boost::filter_iterator<
		sge::sprite::intrusive::ordered::detail::iterator_empty,
		ordered_map_iterator
	>
	filtered_ordered_map_iterator;

	filtered_ordered_map_iterator outer_iterator_;

	typedef
	sge::sprite::intrusive::ordered::detail::range_iterator<
		Choices,
		IsConst
	>
	range_iterator;

	range_iterator inner_iterator_;
};

FCPPT_PP_POP_WARNING

}
}
}
}

#endif
