/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#ifndef SGE_DETAIL_FOREACH_ENUMERATOR_IMPL_HPP_INCLUDED
#define SGE_DETAIL_FOREACH_ENUMERATOR_IMPL_HPP_INCLUDED

template<typename EnumField, typename Callback>
void sge::foreach_enumerator(
	Callback const &fun)
{
	// TODO: find out the underlying type!
	for(unsigned i = 0; i < EnumField::size; ++i)
		fun(
			static_cast<typename EnumField::wrapped_type>(
				i));
}

#endif
