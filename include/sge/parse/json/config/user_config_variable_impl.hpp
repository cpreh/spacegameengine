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


#ifndef SGE_PARSE_JSON_CONFIG_USER_CONFIG_VARIABLE_IMPL_HPP_INCLUDED
#define SGE_PARSE_JSON_CONFIG_USER_CONFIG_VARIABLE_IMPL_HPP_INCLUDED

#include <sge/parse/json/config/user_config_variable_decl.hpp>
#include <sge/parse/json/config/modify_user_value.hpp>
#include <sge/parse/json/find_and_convert_member.hpp>
#include <sge/parse/json/convert_to.hpp>

template<typename T>
sge::parse::json::config::user_config_variable<T>::user_config_variable(
	json::object const &_global_config,
	json::object &_user_config,
	json::path const &_path)
:
	global_config_(
		_global_config),
	user_config_(
		_user_config),
	path_(
		_path),
	value_(
		json::find_and_convert_member<T>(
			global_config_,
			path_)),
	callback_()
{
}

template<typename T>
void
sge::parse::json::config::user_config_variable<T>::value(
	T const &_value)
{
	value_ = 
		_value;
	callback_(
		value_);
}

template<typename T>
T const &
sge::parse::json::config::user_config_variable<T>::value() const
{
	return value_;
}

template<typename T>
fcppt::signal::auto_connection
sge::parse::json::config::user_config_variable<T>::change_callback(
	callback const &f)
{
	return 
		callback_.connect(
			f);
}

template<typename T>
sge::parse::json::config::user_config_variable<T>::~user_config_variable()
{
	config::modify_user_value(
		global_config_,
		user_config_,
		path_,
		json::convert_to(
			value_));
}

#endif
