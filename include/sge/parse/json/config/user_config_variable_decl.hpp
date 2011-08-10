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


#ifndef SGE_PARSE_JSON_CONFIG_USER_CONFIG_VARIABLE_DECL_HPP_INCLUDED
#define SGE_PARSE_JSON_CONFIG_USER_CONFIG_VARIABLE_DECL_HPP_INCLUDED

#include <sge/parse/json/config/user_config_variable_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>
#include <sge/parse/json/path.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/signal/object.hpp>

namespace sge
{
namespace parse
{
namespace json
{
namespace config
{
template<typename T>
class user_config_variable
{
FCPPT_NONCOPYABLE(
	user_config_variable);
public:
	typedef
	void
	callback_fn(
		T const &);

	typedef
	fcppt::function::object<callback_fn>
	callback;

	explicit
	user_config_variable(
		json::object const &,
		json::object &,
		json::path const &);

	void
	value(
		T const &);

	T const &
	value() const;

	fcppt::signal::auto_connection
	change_callback(
		callback const &);

	~user_config_variable();
private:
	json::object const &global_config_;
	json::object &user_config_;
	json::path const path_;
	T value_;
	fcppt::signal::object<callback_fn> callback_;
};
}
}
}
}

#endif
