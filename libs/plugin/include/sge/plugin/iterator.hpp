//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_ITERATOR_HPP_INCLUDED
#define SGE_PLUGIN_ITERATOR_HPP_INCLUDED

#include <sge/plugin/category_array.hpp>
#include <sge/plugin/iterator_fwd.hpp>
#include <sge/plugin/detail/iterator_base_type.hpp>
#include <sge/plugin/detail/instantiate/symbol.hpp>


namespace sge::plugin
{

template<
	typename T
>
class iterator final
:
public
	sge::plugin::detail::iterator_base_type<
		T
	>
{
public:
	using
	base_type
	=
	sge::plugin::detail::iterator_base_type<
		T
	>;

	using
	value_type
	=
	typename
	base_type::value_type;

	using
	reference
	=
	typename
	base_type::reference;

	using
	pointer
	=
	typename
	base_type::pointer;

	using
	difference_type
	=
	typename
	base_type::difference_type;

	using
	iterator_category
	=
	typename
	base_type::iterator_category;

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	explicit
	iterator(
		sge::plugin::category_array::const_iterator
	);

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	void
	increment();

	[[nodiscard]]
	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	bool
	equal(
		iterator const &
	) const;

	[[nodiscard]]
	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	reference
	dereference() const;
private:
	sge::plugin::category_array::const_iterator it_;
};

}

#endif
