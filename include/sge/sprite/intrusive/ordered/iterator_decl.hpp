/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_INTRUSIVE_ORDERED_ITERATOR_DECL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_ORDERED_ITERATOR_DECL_HPP_INCLUDED

#include <sge/sprite/intrusive/detail/ordered_iterator_base.hpp>
#include <sge/sprite/intrusive/detail/ordered_iterator_empty.hpp>
#include <sge/sprite/intrusive/detail/ordered_map.hpp>
#include <sge/sprite/intrusive/ordered/iterator_fwd.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/if.hpp>
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
class iterator
:
	public sge::sprite::intrusive::detail::ordered_iterator_base<
		Choices,
		Order,
		IsConst
	>::type
{
	typedef sge::sprite::intrusive::detail::ordered_iterator_base<
		Choices,
		Order,
		IsConst
	> base_struct;

	typedef typename base_struct::type base;

	typedef typename sge::sprite::intrusive::detail::ordered_map<
		Order,
		Choices
	>::type ordered_map;

	typedef typename boost::mpl::if_c<
		IsConst,
		typename ordered_map::const_iterator,
		typename ordered_map::iterator
	>::type ordered_map_iterator;
public:
	typedef typename base::value_type value_type;

	typedef typename base::reference reference;

	typedef typename base::pointer pointer;

	typedef typename base::difference_type difference_type;

	typedef typename base::iterator_category iterator_category;

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

	typedef boost::filter_iterator<
		sge::sprite::intrusive::detail::ordered_iterator_empty,
		ordered_map_iterator
	> filtered_ordered_map_iterator;

	filtered_ordered_map_iterator outer_iterator_;

	typedef typename base_struct::range_iterator range_iterator;

	range_iterator inner_iterator_;
};

FCPPT_PP_POP_WARNING

}
}
}
}

#endif
