//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_INTRUSIVE_RANGE_IMPL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_RANGE_IMPL_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/intrusive/range_decl.hpp>


template<
	typename Choices,
	bool IsConst
>
sge::sprite::intrusive::range<
	Choices,
	IsConst
>::range(
	reference const _list,
	sge::sprite::count const _size
)
:
	list_(
		_list
	),
	size_(
		_size
	)
{
}

template<
	typename Choices,
	bool IsConst
>
typename sge::sprite::intrusive::range<
	Choices,
	IsConst
>::iterator
sge::sprite::intrusive::range<
	Choices,
	IsConst
>::begin() const
{
	return
		list_.get().begin();
}

template<
	typename Choices,
	bool IsConst
>
typename sge::sprite::intrusive::range<
	Choices,
	IsConst
>::iterator
sge::sprite::intrusive::range<
	Choices,
	IsConst
>::end() const
{
	return
		list_.get().end();
}

template<
	typename Choices,
	bool IsConst
>
sge::sprite::count
sge::sprite::intrusive::range<
	Choices,
	IsConst
>::size() const
{
	return
		size_;
}

template<
	typename Choices,
	bool IsConst
>
bool
sge::sprite::intrusive::range<
	Choices,
	IsConst
>::empty() const
{
	return
		list_.get().empty();
}

template<
	typename Choices,
	bool IsConst
>
template<
	typename Equal
>
void
sge::sprite::intrusive::range<
	Choices,
	IsConst
>::sort(
	Equal const &_equal
) const
{
	list_.get().sort(
		_equal
	);
}

#endif
