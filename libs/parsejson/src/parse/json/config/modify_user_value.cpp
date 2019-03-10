/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/parse/exception.hpp>
#include <sge/parse/json/find_and_convert_member.hpp>
#include <sge/parse/json/make_recursive_objects.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/path_to_string.hpp>
#include <sge/parse/json/config/modify_user_value.hpp>
#include <sge/parse/json/detail/to_fcppt_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_recursive.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/variant/type_info.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


void
sge::parse::json::config::modify_user_value(
	sge::parse::json::object const &structure_json,
	sge::parse::json::object &user_json,
	sge::parse::json::path const &input_path,
	sge::parse::json::value const &new_value
)
{
	FCPPT_ASSERT_PRE(
		!input_path.get().empty()
	);

	sge::parse::json::value const &old_value{
		sge::parse::json::find_and_convert_member<
			sge::parse::json::value
		>(
			structure_json,
			input_path
		)
	};

	if(old_value.get().type_index() != new_value.get().type_index())
		throw
			sge::parse::exception{
				FCPPT_TEXT("Error trying to update the user configuration node \"")
				+
				sge::parse::json::detail::to_fcppt_string(
					sge::parse::json::path_to_string(
						input_path
					)
				)
				+
				FCPPT_TEXT("\", the types of the old and new value didn't match. The old type was \"")
				+
				fcppt::from_std_string(
					fcppt::type_name_from_info(
						fcppt::variant::type_info(
							old_value.get()
						)
					)
				)
				+
				FCPPT_TEXT("\", the new type was \"")
				+
				fcppt::from_std_string(
					fcppt::type_name_from_info(
						fcppt::variant::type_info(
							new_value.get()
						)
					)
				)
			};

	sge::parse::json::object &target =
		// 0 is not permitted, 1 would mean: just take a value from
		// user_json, > 1 means: recursively make a path in the user_json
		input_path.get().size() > 1
		?
			sge::parse::json::make_recursive_objects(
				user_json,
				// TODO: path::pop_back?
				sge::parse::json::path{
					sge::parse::json::path::sequence_type{
						input_path.get().begin(),
						std::prev(
							input_path.get().end()
						)
					}
				}
			)
		:
			user_json;

	sge::parse::json::member_map::iterator const it =
		target.members.find(
			input_path.get().back());

	if(it == target.members.end())
		target.members.insert(
			sge::parse::json::member(
				input_path.get().back(),
				new_value));
	else
		it->second =
			fcppt::make_recursive(
				new_value
			);
}
