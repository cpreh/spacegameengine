/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include "category_array.hpp"
#include "../export.hpp"
#include <boost/iterator/iterator_facade.hpp>
#include <iterator>

namespace sge
{
namespace plugin
{

template<typename T>
class context;

template<typename T>
class iterator;

namespace detail
{

template<typename T>
struct iterator_base_type {
	typedef boost::iterator_facade<
 		iterator<T>,
		context<T>,
		std::random_access_iterator_tag,
		context<T>
	> type;
};

}

template<typename T>
class iterator : public detail::iterator_base_type<T>::type  {
public:
	typedef typename detail::iterator_base_type<T>::type base_type;

	typedef typename base_type::value_type value_type;
	typedef typename base_type::reference reference;
	typedef typename base_type::pointer pointer;
	typedef typename base_type::difference_type difference_type;
	typedef typename base_type::iterator_category iterator_category;

	SGE_SYMBOL explicit iterator(
		category_array::iterator it);

	SGE_SYMBOL void advance(difference_type diff);

	SGE_SYMBOL void increment();

	SGE_SYMBOL void decrement();

	SGE_SYMBOL bool equal(iterator const &r) const;

	SGE_SYMBOL reference dereference() const;

	SGE_SYMBOL difference_type distance_to(iterator const &r) const;
private:
	category_array::iterator it;

	friend class boost::iterator_core_access;
};

}
}

#endif
