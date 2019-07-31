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


namespace sge
{
namespace plugin
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
	typedef
	sge::plugin::detail::iterator_base_type<
		T
	>
	base_type;

	typedef
	typename
	base_type::value_type
	value_type;

	typedef
	typename
	base_type::reference
	reference;

	typedef
	typename
	base_type::pointer
	pointer;

	typedef
	typename
	base_type::difference_type
	difference_type;

	typedef
	typename
	base_type::iterator_category
	iterator_category;

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	explicit
	iterator(
		sge::plugin::category_array::const_iterator
	);

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	void
	increment();

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	bool
	equal(
		iterator const &
	) const;

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	reference
	dereference() const;
private:
	sge::plugin::category_array::const_iterator it_;
};

}
}

#endif
