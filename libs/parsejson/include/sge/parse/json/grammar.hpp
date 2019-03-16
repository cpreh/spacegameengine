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


#ifndef SGE_PARSE_JSON_GRAMMAR_HPP_INCLUDED
#define SGE_PARSE_JSON_GRAMMAR_HPP_INCLUDED

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/grammar_base_fwd.hpp>
#include <sge/parse/json/null.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/parse/grammar_decl.hpp>


namespace sge
{
namespace parse
{
namespace json
{

class grammar
:
	public
		sge::parse::json::grammar_base
{
	FCPPT_NONCOPYABLE(
		grammar
	);
public:
	grammar();

	~grammar();
private:
	base_type<
		sge::parse::json::null
	>
	null_;

	base_type<
		bool
	>
	bool_;

	base_type<
		sge::charconv::utf8_string
	>
	quoted_string_;

	base_type<
		sge::parse::json::array
	>
	array_;

	base_type<
		sge::parse::json::object
	>
	object_;

	base_type<
		sge::parse::json::value
	>
	value_;

	base_type<
		sge::parse::json::start
	>
	start_;
};

}
}
}

#endif
