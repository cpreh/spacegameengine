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


#include <sge/library/function_not_found.hpp>
#include <sge/library/error.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>

sge::library::function_not_found::function_not_found(
	fcppt::string const &_lib,
	std::string const &_func
)
:
	sge::exception(
		FCPPT_TEXT("Failed to load function ")
		+ fcppt::from_std_string(_func)
		+ FCPPT_TEXT(" from object::library ")
		+ _lib
		+ FCPPT_TEXT(" : ")
		+ error()
	),
	lib_(_lib),
	func_(_func)
{}


fcppt::string const &
sge::library::function_not_found::lib() const
{
	return lib_;
}

sge::library::function_string const &
sge::library::function_not_found::func() const
{
	return func_;
}

sge::library::function_not_found::~function_not_found() throw()
{}
