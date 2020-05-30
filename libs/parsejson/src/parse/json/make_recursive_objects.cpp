//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/exception.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_value.hpp>
#include <sge/parse/json/get_exn.hpp>
#include <sge/parse/json/get_exn_message.hpp>
#include <sge/parse/json/make_recursive_objects.hpp>
#include <sge/parse/json/make_value.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/parse/json/path_to_string.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/detail/to_fcppt_string.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/variant/type_info.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

using
object_reference
=
fcppt::reference<
	sge::parse::json::object
>;

object_reference
create_or_navigate_path(
	sge::parse::json::path const &_input_path,
	object_reference const _old,
	sge::charconv::utf8_string const &_new_member
)
{
	return
		fcppt::optional::maybe(
			sge::parse::json::find_member_value(
				fcppt::make_ref(
					_old.get().members
				),
				_new_member
			),
			[
				&_old,
				&_new_member
			]()
			-> object_reference
			{
				std::pair<
					sge::parse::json::member_map::iterator,
					bool
				> const insert_ret{
					_old.get().members.insert(
						sge::parse::json::member(
							_new_member,
							sge::parse::json::make_value(
								sge::parse::json::object{
									sge::parse::json::member_map{}
								}
							)
						)
					)
				};

				FCPPT_ASSERT_ERROR(
					insert_ret.second
				);

				return
					sge::parse::json::get_exn<
						sge::parse::json::object
					>(
						fcppt::make_ref(
							insert_ret.first->second.get()
						)
					);
			},
			[
				&_input_path,
				&_new_member
			](
				fcppt::reference<
					sge::parse::json::value
				> const _value
			)
			-> object_reference
			{
				return
					sge::parse::json::get_exn_message<
						sge::parse::json::object
					>(
						_value,
						[
							&_input_path,
							&_new_member
						]{
							return
								FCPPT_TEXT("Couldn't navigate to (make_recursive) \"")
								+
								sge::parse::json::detail::to_fcppt_string(
									sge::parse::json::path_to_string(
										_input_path
									)
								)
								+
								FCPPT_TEXT("\", stopped at \"")
								+
								sge::parse::json::detail::to_fcppt_string(
									_new_member
								);
						}
					);
			}
		);
}

}

fcppt::reference<
	sge::parse::json::object
>
sge::parse::json::make_recursive_objects(
	fcppt::reference<
		sge::parse::json::object
	> const _input_object,
	sge::parse::json::path const &_input_path
)
{
	return
		fcppt::algorithm::fold(
			_input_path.get(),
			_input_object,
			[
				&_input_path
			](
				sge::charconv::utf8_string const &_string,
				fcppt::reference<
					sge::parse::json::object
				> const _ref
			)
			{
				return
					create_or_navigate_path(
						_input_path,
						_ref,
						_string
					);
			}
		);
}
