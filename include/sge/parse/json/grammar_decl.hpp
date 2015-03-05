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


#ifndef SGE_PARSE_JSON_GRAMMAR_DECL_HPP_INCLUDED
#define SGE_PARSE_JSON_GRAMMAR_DECL_HPP_INCLUDED

#include <sge/parse/encoding.hpp>
#include <sge/parse/optional_error_string.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/float_type.hpp>
#include <sge/parse/json/grammar_fwd.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/null.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/string.hpp>
#include <sge/parse/json/detail/member_wrapper.hpp>
#include <sge/parse/json/detail/value_wrapper.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/include/qi_grammar.hpp>
#include <boost/spirit/include/qi_int.hpp>
#include <boost/spirit/include/qi_real.hpp>
#include <boost/spirit/include/qi_rule.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace json
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename In
>
class grammar final
:
	public boost::spirit::qi::grammar<
		In,
		sge::parse::json::start(),
		sge::parse::encoding::space_type
	>
{
	FCPPT_NONCOPYABLE(
		grammar
	);
public:
	typedef sge::parse::encoding::space_type space_type;

	grammar();

	~grammar();

	sge::parse::optional_error_string const &
	error_string() const;
private:
	boost::spirit::qi::int_parser<
		sge::parse::json::int_type
	> int_;

	boost::spirit::qi::real_parser<
		sge::parse::json::float_type,
		boost::spirit::qi::strict_real_policies<
			json::float_type
		>
	> strict_float_;

	boost::spirit::qi::rule<
		In,
		sge::parse::json::null(),
		space_type
	> null_;

	boost::spirit::qi::rule<
		In,
		bool(),
		space_type
	> bool_;

	boost::spirit::qi::rule<
		In,
		sge::parse::json::string(),
		space_type
	> quoted_string_;

	boost::spirit::qi::rule<
		In,
		sge::parse::json::element_vector(),
		space_type
	> element_vector_;

	boost::spirit::qi::rule<
		In,
		sge::parse::json::array(),
		space_type
	> array_;

	boost::spirit::qi::rule<
		In,
		sge::parse::json::detail::value_wrapper(),
		space_type
	> value_wrapper_;

	boost::spirit::qi::rule<
		In,
		sge::parse::json::detail::member_wrapper(),
		space_type
	> member_wrapper_;

	boost::spirit::qi::rule<
		In,
		sge::parse::json::member_map(),
		space_type
	> member_map_;

	boost::spirit::qi::rule<
		In,
		sge::parse::json::object(),
		space_type
	> object_;

	boost::spirit::qi::rule<
		In,
		sge::parse::json::start(),
		space_type
	> start_;

	sge::parse::optional_error_string error_string_;
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
