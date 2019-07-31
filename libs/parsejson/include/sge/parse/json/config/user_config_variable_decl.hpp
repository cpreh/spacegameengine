//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_CONFIG_USER_CONFIG_VARIABLE_DECL_HPP_INCLUDED
#define SGE_PARSE_JSON_CONFIG_USER_CONFIG_VARIABLE_DECL_HPP_INCLUDED

#include <sge/parse/json/object_fwd.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/parse/json/config/user_config_variable_fwd.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sge
{
namespace parse
{
namespace json
{
namespace config
{

template<
	typename T
>
class user_config_variable
{
	FCPPT_NONCOPYABLE(
		user_config_variable
	);
public:
	typedef
	void
	callback_fn(
		T const &
	);

	typedef
	fcppt::function<
		callback_fn
	>
	callback;

	user_config_variable(
		sge::parse::json::object const &,
		sge::parse::json::object &,
		sge::parse::json::path const &
	);

	void
	value(
		T const &
	);

	T const &
	value() const;

	fcppt::signal::auto_connection
	change_callback(
		callback const &
	);

	~user_config_variable();
private:
	sge::parse::json::object const &global_config_;

	sge::parse::json::object &user_config_;

	sge::parse::json::path const path_;

	T value_;

	fcppt::signal::object<
		callback_fn
	> callback_;
};

}
}
}
}

#endif
