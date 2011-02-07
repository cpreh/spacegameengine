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


#include "error.hpp"
#include <sge/plugin/library/symbol_not_found.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>

sge::plugin::library::symbol_not_found::symbol_not_found(
	fcppt::string const &_library_name,
	std::string const &_symbol
)
:
	sge::plugin::library::exception(
		FCPPT_TEXT("Failed to load function ")
		+
		fcppt::from_std_string(
			_symbol
		)
		+
		FCPPT_TEXT(" from object::library ")
		+
		_library_name
		+
		FCPPT_TEXT(" : ")
		+
		library::error()
	),
	library_name_(_library_name),
	symbol_(_symbol)
{
}

fcppt::string const &
sge::plugin::library::symbol_not_found::library_name() const
{
	return library_name_;
}

sge::plugin::library::symbol_string const &
sge::plugin::library::function_not_found::symbol() const
{
	return symbol_;
}

sge::plugin::library::function_not_found::~function_not_found() throw()
{
}
