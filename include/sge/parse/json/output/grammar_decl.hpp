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


#ifndef SGE_PARSE_JSON_OUTPUT_GRAMMAR_DECL_HPP_INCLUDED
#define SGE_PARSE_JSON_OUTPUT_GRAMMAR_DECL_HPP_INCLUDED

#include <sge/parse/json/array.hpp>
#include <sge/parse/json/float_type.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/null.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/string.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/output/grammar_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/include/karma_grammar.hpp>
#include <boost/spirit/include/karma_int.hpp>
#include <boost/spirit/include/karma_real.hpp>
#include <boost/spirit/include/karma_rule.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace json
{
namespace output
{

template<
	typename Out
>
class grammar final
:
	public boost::spirit::karma::grammar<
		Out,
		sge::parse::json::start()
	>
{
	FCPPT_NONCOPYABLE(
		grammar
	);
public:
	grammar();

	~grammar();
private:
	boost::spirit::karma::int_generator<
		sge::parse::json::int_type
	> int_;

	boost::spirit::karma::real_generator<
		sge::parse::json::float_type
	> float_;

	boost::spirit::karma::rule<
		Out,
		sge::parse::json::null
	> null_;

	boost::spirit::karma::rule<
		Out,
		sge::parse::json::string()
	> quoted_string_;

	boost::spirit::karma::rule<
		Out,
		sge::parse::json::array()
	> array_;

	boost::spirit::karma::rule<
		Out,
		sge::parse::json::value()
	> value_;

	boost::spirit::karma::rule<
		Out,
		sge::parse::json::member()
	> member_;

	boost::spirit::karma::rule<
		Out,
		sge::parse::json::object()
	> object_;

	boost::spirit::karma::rule<
		Out,
		sge::parse::json::start()
	> start_;
};

}
}
}
}

#endif
