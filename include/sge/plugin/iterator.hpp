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


#ifndef SGE_PLUGIN_ITERATOR_HPP_INCLUDED
#define SGE_PLUGIN_ITERATOR_HPP_INCLUDED

#include <sge/plugin/category_array.hpp>
#include <sge/plugin/instantiate_symbol.hpp>
#include <sge/plugin/iterator_fwd.hpp>
#include <sge/plugin/detail/iterator_base_type.hpp>


namespace sge
{
namespace plugin
{

template<
	typename T
>
class iterator
:
public
	detail::iterator_base_type<
		T
	>::type
{
public:
	typedef typename detail::iterator_base_type<T>::type base_type;

	typedef typename base_type::value_type value_type;

	typedef typename base_type::reference reference;

	typedef typename base_type::pointer pointer;

	typedef typename base_type::difference_type difference_type;

	typedef typename base_type::iterator_category iterator_category;

	SGE_PLUGIN_INSTANTIATE_SYMBOL
	explicit iterator(
		category_array::iterator
	);

	SGE_PLUGIN_INSTANTIATE_SYMBOL
	void
	advance(
		difference_type
	);

	SGE_PLUGIN_INSTANTIATE_SYMBOL
	void
	increment();

	SGE_PLUGIN_INSTANTIATE_SYMBOL
	void
	decrement();

	SGE_PLUGIN_INSTANTIATE_SYMBOL
	bool
	equal(
		iterator const &
	) const;

	SGE_PLUGIN_INSTANTIATE_SYMBOL
	reference
	dereference() const;

	SGE_PLUGIN_INSTANTIATE_SYMBOL
	difference_type
	distance_to(
		iterator const &
	) const;
private:
	category_array::iterator it_;

	friend class boost::iterator_core_access;
};

}
}

#endif
