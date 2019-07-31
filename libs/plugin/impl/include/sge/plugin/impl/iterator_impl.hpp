//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_IMPL_ITERATOR_IMPL_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_ITERATOR_IMPL_HPP_INCLUDED

#include <sge/plugin/category_array.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/iterator.hpp>


template<
	typename Type
>
sge::plugin::iterator<
	Type
>::iterator(
	sge::plugin::category_array::const_iterator const _it
)
:
	it_{
		_it
	}
{
}

template<
	typename Type
>
void
sge::plugin::iterator<
	Type
>::increment()
{
	++it_;
}

template<
	typename Type
>
bool
sge::plugin::iterator<
	Type
>::equal(
	iterator const &_other
) const
{
	return
		it_
		==
		_other.it_;
}

template<
	typename Type
>
typename sge::plugin::iterator<
	Type
>::reference
sge::plugin::iterator<
	Type
>::dereference() const
{
	return
		sge::plugin::context<
			Type
		>(
			it_->get()
		);
}

#endif
