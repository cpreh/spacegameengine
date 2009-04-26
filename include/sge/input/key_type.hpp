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



#ifndef SGE_INPUT_KEY_TYPE_HPP_INCLUDED
#define SGE_INPUT_KEY_TYPE_HPP_INCLUDED

#include <sge/input/key_code.hpp>
#include <sge/export.hpp>
#include <sge/string.hpp>

namespace sge
{
namespace input
{

class key_type {
public:
	typedef sge::string        string;
	typedef string::value_type char_type;

	SGE_SYMBOL explicit key_type(
		string const &name = string(),
		key_code code = kc::none,
		char_type char_code = 0);

	SGE_SYMBOL string const &name() const;
	SGE_SYMBOL key_code code() const;
	SGE_SYMBOL char_type char_code() const;

	SGE_SYMBOL void char_code(char_type);
private:
	string    name_;
	key_code  code_;
	char_type char_code_;
};

SGE_SYMBOL bool operator<(key_type const &l, key_type const &r);

SGE_SYMBOL bool operator==(key_type const &l, key_type const &r);

SGE_SYMBOL bool operator!=(key_type const &l, key_type const &r);

}
}

#endif
