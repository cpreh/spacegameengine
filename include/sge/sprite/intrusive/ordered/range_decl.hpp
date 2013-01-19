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


#ifndef SGE_SPRITE_INTRUSIVE_ORDERED_RANGE_DECL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_ORDERED_RANGE_DECL_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/intrusive/detail/ordered_map.hpp>
#include <sge/sprite/intrusive/ordered/iterator_fwd.hpp>
#include <sge/sprite/intrusive/ordered/range_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
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

template<
	typename Choices,
	typename Order,
	bool IsConst
>
class range
{
	FCPPT_NONASSIGNABLE(
		range
	);

	typedef typename sge::sprite::intrusive::detail::ordered_map<
		Order,
		Choices
	>::type ordered_map;
public:
	typedef typename boost::mpl::if_c<
		IsConst,
		ordered_map const &,
		ordered_map &
	>::type ordered_map_reference;

	typedef sge::sprite::intrusive::ordered::iterator<
		Choices,
		Order,
		IsConst
	> iterator;

	explicit
	range(
		ordered_map_reference
	);

	iterator const
	begin() const;

	iterator const
	end() const;

	sge::sprite::count const
	size() const;

	bool
	empty() const;

	template<
		typename Equal
	>
	void
	sort(
		Equal const &
	) const;
private:
	ordered_map_reference ordered_map_;

	sge::sprite::count const size_;
};

}
}
}
}

#endif
