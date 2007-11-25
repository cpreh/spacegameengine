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


#include "../../math/utility.hpp"
#include "../key_type.hpp"

sge::key_type::key_type(const string& name_, const key_code code_, const char_type char_code_)
 : name_(name_),
   code_(code_),
   char_code_(char_code_)
{}

const sge::key_type::string& sge::key_type::name() const
{
	return name_;
}

sge::key_code sge::key_type::code() const
{
	return code_;
}

sge::key_type::char_type sge::key_type::char_code() const
{
	return char_code_;
}

void sge::key_type::char_code(const char_type ch)
{
	char_code_ = ch;
}


sge::key_pair::key_pair(const key_type& key_, const key_state value_)
: key_(key_),
  value_(value_)
{}

const sge::key_type& sge::key_pair::key() const
{
	return key_;
}

sge::key_state sge::key_pair::value() const
{
	return value_;
}
