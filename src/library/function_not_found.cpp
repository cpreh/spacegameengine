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


#include <sge/library/function_not_found.hpp>
#include <sge/library/error.hpp>
#include <sge/iconv.hpp>
#include <sge/text.hpp>

sge::library::function_not_found::function_not_found(
	string const &lib_,
	std::string const &func_)
:
	exception(
		SGE_TEXT("Failed to load function ")
		+ iconv(func_)
		+ SGE_TEXT(" from object::library ")
		+ lib_
		+ SGE_TEXT(" : ")
		+ error()),
	lib_(lib_),
	func_(func_)
{}


sge::string const &
sge::library::function_not_found::lib() const
{
	return lib_;
}

sge::library::function_string const &
sge::library::function_not_found::func() const
{
	return func_;
}
