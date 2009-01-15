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


#include <sge/console/console.hpp>
#include <sge/console/singleton.hpp>

void sge::con::eval(
	string const &s)
{
	instance().eval(s);
}

sge::signals::connection const
sge::con::chat_callback(
	callback const &c)
{
	return instance().chat.connect(c);
}

sge::signals::connection const
sge::con::add(
	string const &name,
	callback const &c)
{
	return instance().add(name, c);
}

void sge::con::prefix(
	string::value_type const &c)
{
	instance().prefix = c;
}

sge::string::value_type sge::con::prefix()
{
	return instance().prefix;
}

void sge::con::read_config(
	filesystem::path const &s)
{
	instance().read_config(s);
}

sge::con::var_map const &
sge::con::vars()
{
	return instance().vars;
}

sge::con::callback_map const &
sge::con::funcs()
{
	return instance().funcs;
}

sge::string const
sge::con::get_var(
	sge::string const &name)
{
	return instance().var(name);
}

void sge::con::set_var(
	sge::string const &name,
	sge::string const &value)
{
	instance().var(name,value);
}

void sge::con::latch(
	sge::string const &name,
	sge::string const &value)
{
	instance().latch(name,value);
}
