/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/parse/json/array.hpp>
#include <sge/parse/json/const_optional_object_ref.hpp>
#include <sge/parse/json/find_member_return_type.hpp>
#include <sge/parse/json/find_member_value.hpp>
#include <sge/parse/json/find_object.hpp>
#include <sge/parse/json/get_exn_message.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/optional_object_ref.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/parse/json/path_to_string.hpp>
#include <fcppt/const.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/reference_wrapper_impl.hpp>
#include <fcppt/text.hpp>


namespace
{

template<
	typename Object
>
fcppt::optional<
	Object &
>
find_object_impl(
	Object &_input_object,
	sge::parse::json::path const &_path)
{
	typedef
	fcppt::reference_wrapper<
		Object
	>
	object_ref;

	typedef
	fcppt::optional<
		Object &
	>
	result_type;

	object_ref current_object(
		_input_object
	);

	for(
		auto const &current_member
		:
		_path
	)
	{
		typedef
		typename
		sge::parse::json::find_member_return_type<
			sge::parse::json::value,
			Object
		>::element_type
		value_reference;

		if(
			fcppt::maybe(
				sge::parse::json::find_member_value(
					current_object.get().members,
					current_member
				),
				fcppt::const_(
					true
				),
				[
					&current_object,
					&current_member,
					&_path
				](
					value_reference _val
				)
				{
					current_object =
						object_ref(
							sge::parse::json::get_exn_message<
								sge::parse::json::object
							>(
								_val,
								[
									&_path,
									&current_member
								]{
									return
										FCPPT_TEXT("Couldn't navigate to \"")
										+
										sge::parse::json::path_to_string(
											_path
										)
										+
										FCPPT_TEXT("\", stopped at \"")
										+
										current_member;
								}
							)
						);

					return
						false;
				}
			)
		)
			return
				result_type();
	}

	return
		result_type(
			current_object.get()
		);
}

}

sge::parse::json::optional_object_ref
sge::parse::json::find_object(
	sge::parse::json::object &_input_object,
	sge::parse::json::path const &_path
)
{
	return
		find_object_impl(
			_input_object,
			_path
		);
}

sge::parse::json::const_optional_object_ref
sge::parse::json::find_object(
	sge::parse::json::object const &_input_object,
	sge::parse::json::path const &_path
)
{
	return
		find_object_impl(
			_input_object,
			_path
		);
}
