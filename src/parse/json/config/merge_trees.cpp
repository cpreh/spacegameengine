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


#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_value.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/config/merge_trees.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/string.hpp>
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
public:
	typedef
	sge::parse::json::value
	result_type;

	result_type
	operator()(
		sge::parse::json::object const &original,
		sge::parse::json::object const &update) const
	{
		return
			sge::parse::json::config::merge_trees(
				original,
				update);
	}

	template<typename T1,typename T2>
	result_type
	operator()(
		T1 const &,
		T2 const &update) const
	{
		return update;
	}
};
}

sge::parse::json::object const
sge::parse::json::config::merge_trees(
	sge::parse::json::object const &original,
	sge::parse::json::object const &update)
{
	sge::parse::json::object result;

	typedef
	std::set<fcppt::string>
	string_set;

	string_set const union_set(
		fcppt::algorithm::set_union(
			fcppt::algorithm::key_set<
				string_set
			>(
				original.members
			),
			fcppt::algorithm::key_set<
				string_set
			>(
				update.members
			)
		)
	);

	for(
		string_set::const_iterator key =
			union_set.begin();
		key != union_set.end();
		++key)
	{
		typedef fcppt::optional<
			sge::parse::json::value const &
		> optional_value;

		optional_value const
			original_value(
				sge::parse::json::find_member_value(
					original.members,
					*key
				)
			),
			update_value(
				sge::parse::json::find_member_value(
					update.members,
					*key
				)
			);

		// Object exists only in the update? Then copy
		if (!original_value)
		{
			result.members.insert(
				json::member(
					*key,
					*update_value
				)
			);

			continue;
		}

		// Object exists only in the original? Then copy
		if (!update_value)
		{
			result.members.insert(
				json::member(
					*key,
					*original_value
				)
			);

			continue;
		}

		// Both objects have the key, then merge!
		result.members.insert(
			json::member(
				*key,
				fcppt::variant::apply_binary(
					visitor(),
					*original_value,
					*update_value
				)
			)
		);
	}

	return result;
}
