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
#include <sge/parse/json/find_member_value.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/config/merge_trees.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/optional_combine.hpp>
#include <fcppt/string.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/algorithm/key_set.hpp>
#include <fcppt/algorithm/set_union.hpp>
#include <fcppt/variant/apply_binary.hpp>
#include <fcppt/config/external_begin.hpp>
#include <set>
#include <fcppt/config/external_end.hpp>


namespace
{

struct visitor
{
	typedef
	sge::parse::json::value
	result_type;

	result_type
	operator()(
		sge::parse::json::object const &_original,
		sge::parse::json::object const &_update
	) const
	{
		return
			sge::parse::json::config::merge_trees(
				_original,
				_update
			);
	}

	template<
		typename T1,
		typename T2
	>
	result_type
	operator()(
		T1 const &,
		T2 const &_update
	) const
	{
		return
			_update;
	}
};

}

sge::parse::json::object
sge::parse::json::config::merge_trees(
	sge::parse::json::object const &_original,
	sge::parse::json::object const &_update
)
{
	typedef
	std::set<
		fcppt::string
	>
	string_set;

	return
		sge::parse::json::object(
			fcppt::algorithm::map_optional<
				sge::parse::json::member_map
			>(
				fcppt::algorithm::set_union(
					fcppt::algorithm::key_set<
						string_set
					>(
						_original.members
					),
					fcppt::algorithm::key_set<
						string_set
					>(
						_update.members
					)
				),
				[
					&_original,
					&_update
				](
					fcppt::string const &_key
				)
				{
					return
						fcppt::optional_bind_construct(
							fcppt::optional_combine(
								sge::parse::json::find_member_value(
									_original.members,
									_key
								),
								sge::parse::json::find_member_value(
									_update.members,
									_key
								),
								[](
									sge::parse::json::value const &_original_value,
									sge::parse::json::value const &_update_value
								)
								{
									return
										fcppt::variant::apply_binary(
											visitor(),
											_original_value,
											_update_value
										);
								}
							),
							[
								&_key
							](
								sge::parse::json::value const &_combined
							)
							{
								return
									sge::parse::json::member(
										_key,
										_combined
									);
							}
						);
				}
			)
		);
}
