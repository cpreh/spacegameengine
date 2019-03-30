/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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
