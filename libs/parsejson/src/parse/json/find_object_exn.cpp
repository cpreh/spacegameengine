//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/parse/exception.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_object.hpp>
#include <sge/parse/json/find_object_exn.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/parse/json/path_to_string.hpp>
#include <sge/parse/json/detail/to_fcppt_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/to_exception.hpp>


namespace
{

template<
	typename Object
>
fcppt::reference<
	Object
>
find_object_exn_impl(
	fcppt::reference<
		Object
	> const _input_object,
	sge::parse::json::path const &_path
)
{
	return
		fcppt::optional::to_exception(
			sge::parse::json::find_object(
				_input_object,
				_path
			),
			[
				&_path
			]{
				return
					sge::parse::exception(
						FCPPT_TEXT("Couldn't navigate to \"")
						+
						sge::parse::json::detail::to_fcppt_string(
							sge::parse::json::path_to_string(
								_path
							)
						)
						+
						FCPPT_TEXT("\" because we couldn't find the object here!")
					);
			}
		);
}

}

fcppt::reference<
	sge::parse::json::object
>
sge::parse::json::find_object_exn(
	fcppt::reference<
		sge::parse::json::object
	> const _input_object,
	sge::parse::json::path const &_path
)
{
	return
		find_object_exn_impl(
			_input_object,
			_path
		);
}

fcppt::reference<
	sge::parse::json::object const
>
sge::parse::json::find_object_exn(
	fcppt::reference<
		sge::parse::json::object const
	> const _input_object,
	sge::parse::json::path const &_path
)
{
	return
		find_object_exn_impl(
			_input_object,
			_path
		);
}
