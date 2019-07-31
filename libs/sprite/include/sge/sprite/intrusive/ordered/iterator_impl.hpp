//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_INTRUSIVE_ORDERED_ITERATOR_IMPL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_ORDERED_ITERATOR_IMPL_HPP_INCLUDED

#include <sge/sprite/intrusive/ordered/iterator_decl.hpp>
#include <sge/sprite/intrusive/ordered/detail/iterator_empty.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

template<
	typename Choices,
	typename Order,
	bool IsConst
>
sge::sprite::intrusive::ordered::iterator<
	Choices,
	Order,
	IsConst
>::iterator(
	ordered_map_iterator const _current_outer_iterator,
	ordered_map_iterator const _outer_iterator_end
)
:
	outer_iterator_(
		sge::sprite::intrusive::ordered::detail::iterator_empty(),
		_current_outer_iterator,
		_outer_iterator_end
	),
	inner_iterator_(
		this->is_end()
		?
			range_iterator()
		:
			outer_iterator_.base()->second->range().begin()
	)
{
}

FCPPT_PP_POP_WARNING

template<
	typename Choices,
	typename Order,
	bool IsConst
>
void
sge::sprite::intrusive::ordered::iterator<
	Choices,
	Order,
	IsConst
>::increment()
{
	++inner_iterator_;

	if(
		inner_iterator_
		== outer_iterator_.base()->second->range().end()
	)
	{
		++outer_iterator_;

		if(
			!this->is_end()
		)
			inner_iterator_ =
				outer_iterator_.base()->second->range().begin();
	}
}

template<
	typename Choices,
	typename Order,
	bool IsConst
>
typename sge::sprite::intrusive::ordered::iterator<
	Choices,
	Order,
	IsConst
>::reference
sge::sprite::intrusive::ordered::iterator<
	Choices,
	Order,
	IsConst
>::dereference() const
{
	return
		*inner_iterator_;
}

template<
	typename Choices,
	typename Order,
	bool IsConst
>
bool
sge::sprite::intrusive::ordered::iterator<
	Choices,
	Order,
	IsConst
>::equal(
	iterator const &_other
) const
{
	return
		outer_iterator_
		==
		_other.outer_iterator_
		&&
		(
			(
				this->is_end()
				&&
				_other.is_end()
			)
			||
			(
				inner_iterator_
				==
				_other.inner_iterator_
			)
		);
}

template<
	typename Choices,
	typename Order,
	bool IsConst
>
bool
sge::sprite::intrusive::ordered::iterator<
	Choices,
	Order,
	IsConst
>::is_end() const
{
	return
		outer_iterator_.base()
		==
		outer_iterator_.end();
}

#endif
