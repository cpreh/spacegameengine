/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_LIBRARY_OBJECT_IMPL_HPP_INCLUDED
#define SGE_LIBRARY_OBJECT_IMPL_HPP_INCLUDED

#include <sge/library/object.hpp>
#include <sge/library/function_not_found.hpp>
#include <fcppt/filesystem/path_to_string.hpp>

template<
	typename Fun
>
Fun
sge::library::object::load_function(
	function_string const &_fun
)
{
	Fun const ptr = reinterpret_cast<Fun>(load_address_base(_fun));
	if(!ptr)
		throw function_not_found(
			fcppt::filesystem::path_to_string(
				name().string()
			),
			_fun
		);
	return ptr;
}

#endif
