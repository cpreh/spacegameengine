//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_CONFIG_USER_CONFIG_VARIABLE_IMPL_HPP_INCLUDED
#define SGE_PARSE_JSON_CONFIG_USER_CONFIG_VARIABLE_IMPL_HPP_INCLUDED

#include <sge/parse/json/convert_to.hpp>
#include <sge/parse/json/find_and_convert_member.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/parse/json/config/modify_user_value.hpp>
#include <sge/parse/json/config/user_config_variable_decl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>


template<typename T>
sge::parse::json::config::user_config_variable<T>::user_config_variable(
	sge::parse::json::object const &_global_config,
	sge::parse::json::object &_user_config,
	sge::parse::json::path const &_path)
:
	global_config_(
		_global_config),
	user_config_(
		_user_config),
	path_(
		_path),
	value_(
		sge::parse::json::find_and_convert_member<T>(
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
	sge::parse::json::config::modify_user_value(
		global_config_,
		user_config_,
		path_,
		sge::parse::json::convert_to(
			value_));
}

#endif
