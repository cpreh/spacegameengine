/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_PARSE_INI_GRAMMAR_DECL_HPP_INCLUDED
#define SGE_PARSE_INI_GRAMMAR_DECL_HPP_INCLUDED

#include <sge/parse/encoding.hpp>
#include <sge/parse/optional_error_string.hpp>
#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/grammar_fwd.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/section_vector.hpp>
#include <sge/parse/ini/start.hpp>
#include <sge/parse/ini/string.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/include/qi_grammar.hpp>
#include <boost/spirit/include/qi_rule.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace ini
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename In
>
class grammar
:
	public boost::spirit::qi::grammar<
		In,
		sge::parse::ini::start(),
		sge::parse::encoding::blank_type
	>
{
	FCPPT_NONCOPYABLE(
		grammar
	);
public:
	grammar();

	~grammar();

	sge::parse::optional_error_string const &
	error_string() const;
private:
	boost::spirit::qi::rule<
		In,
		sge::parse::ini::entry(),
		sge::parse::encoding::blank_type
	> entry_;

	boost::spirit::qi::rule<
		In,
		sge::parse::ini::string(),
		sge::parse::encoding::blank_type
	> header_;

	boost::spirit::qi::rule	<
		In,
		sge::parse::ini::section(),
		sge::parse::encoding::blank_type
	> section_;

	boost::spirit::qi::rule<
		In,
		sge::parse::ini::section_vector(),
		sge::parse::encoding::blank_type
	> section_vector_;

	boost::spirit::qi::rule<
		In,
		sge::parse::ini::start(),
		sge::parse::encoding::blank_type
	> ini_;

	sge::parse::optional_error_string error_string_;
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
