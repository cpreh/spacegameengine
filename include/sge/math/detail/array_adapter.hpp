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


#ifndef SGE_MATH_DETAIL_ARRAY_ADAPTER_HPP_INCLUDED
#define SGE_MATH_DETAIL_ARRAY_ADAPTER_HPP_INCLUDED

namespace sge
{
namespace math
{
namespace detail
{

template<
	typename Derived
>
struct array_adapter {
	typename Derived::reference at(
		typename Derived::size_type);
	typename Derived::const_reference at(
		typename Derived::size_type) const;

	typename Derived::pointer data_end();
	typename Derived::const_pointer data_end() const;

	typename Derived::iterator begin();
	typename Derived::const_iterator begin() const;
	typename Derived::iterator end();
	typename Derived::const_iterator end() const;
	typename Derived::reverse_iterator rbegin();
	typename Derived::const_reverse_iterator rbegin() const;
	typename Derived::reverse_iterator rend();
	typename Derived::const_reverse_iterator rend() const;

	bool empty() const;

	bool operator==(
		Derived const &) const;
	bool operator!=(
		Derived const &) const;
private:
	Derived &this_();
	Derived const &this_() const;
};

}
}
}

#endif
