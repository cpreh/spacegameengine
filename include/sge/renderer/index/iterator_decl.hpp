/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_INDEX_ITERATOR_DECL_HPP_INCLUDED
#define SGE_RENDERER_INDEX_ITERATOR_DECL_HPP_INCLUDED

#include <sge/renderer/index/iterator_fwd.hpp>
#include <sge/renderer/index/to_nonconst_format.hpp>
#include <sge/renderer/index/detail/iterator_base.hpp>
#include <sge/symbol.hpp>
#include <boost/iterator/iterator_facade.hpp>

namespace sge
{
namespace renderer
{
namespace index
{

template<
	typename Format
>
class iterator
:
	public detail::iterator_base<
		Format
	>::type
{
public:
	typedef typename detail::iterator_base<
		Format
	>::type base;

	typedef typename base::value_type value_type;

	typedef typename base::reference reference;

	typedef typename Format::pointer pointer;

	typedef typename base::difference_type difference_type;

	typedef typename base::iterator_category iterator_category;

	friend class boost::iterator_core_access;

	SGE_SYMBOL
	explicit iterator(
		pointer
	);

	typedef index::iterator<
		typename index::to_nonconst_format<
			Format
		>::type
	> nonconst_iterator;

	SGE_SYMBOL
	iterator(
		nonconst_iterator const &
	);

	SGE_SYMBOL
	pointer
	data() const;
private:
	SGE_SYMBOL
	void
	advance(
		difference_type
	);

	SGE_SYMBOL
	void
	increment();

	SGE_SYMBOL
	void
	decrement();

	SGE_SYMBOL
	bool
	equal(
		iterator const &
	) const;

	SGE_SYMBOL
	difference_type
	distance_to(
		iterator const &
	) const;

	SGE_SYMBOL
	reference
	dereference() const;

	pointer data_;
};

}
}
}

#endif
