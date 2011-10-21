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
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_name_equal.hpp>
#include <sge/parse/json/member_vector.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/config/merge_trees.hpp>
#include <fcppt/string.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/home/phoenix/bind.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <algorithm>
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

namespace sge
{
namespace parse
{
namespace stdlib
{
template<typename T>
std::set<T> const
union_(
	std::set<T> result,
	std::set<T> const &t)
{
	std::copy(
		t.begin(),
		t.end(),
		std::inserter(
			result,
			result.end()));
	return result;
}
}
}
}

namespace sge
{
namespace parse
{
namespace json
{
std::set<fcppt::string> const
key_set(
	sge::parse::json::object const &o)
{
	return
		fcppt::algorithm::map<std::set<fcppt::string> >(
			o.members,
			boost::phoenix::bind(
				&sge::parse::json::member::name,
				boost::phoenix::arg_names::arg1));
}
}
}
}

sge::parse::json::object const
sge::parse::json::config::merge_trees(
	sge::parse::json::object const &original,
	sge::parse::json::object const &update)
{
	using namespace sge::parse::json;

	sge::parse::json::object result;

	typedef
	std::set<fcppt::string>
	string_set;

	string_set const union_set =
		sge::parse::stdlib::union_(
			key_set(
				original),
			key_set(
				update));

	for(
		string_set::const_iterator key =
			union_set.begin();
		key != union_set.end();
		++key)
	{
		member_vector::const_iterator
			original_it =
				std::find_if(
					original.members.begin(),
					original.members.end(),
					member_name_equal(
						*key)),
			update_it =
				std::find_if(
					update.members.begin(),
					update.members.end(),
					member_name_equal(
						*key));

		// Object exists only in the update? Then copy
		if (original_it == original.members.end())
		{
			result.members.push_back(
				*update_it);
			continue;
		}

		// Object exists only in the original? Then copy
		if (update_it == update.members.end())
		{
			result.members.push_back(
				*original_it);
			continue;
		}

		// Both objects have the key, then merge!
		result.members.push_back(
			member(
				*key,
				boost::apply_visitor(
					visitor(),
					original_it->value,
					update_it->value)));
	}

	return result;
}
