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


#ifndef SGE_SRC_CONSOLE_EVAL_GRAMMAR_DECL_HPP_INCLUDED
#define SGE_SRC_CONSOLE_EVAL_GRAMMAR_DECL_HPP_INCLUDED

#include <sge/console/arg_list.hpp>
#include <sge/font/string.hpp>
#include <sge/src/console/eval_grammar_fwd.hpp>
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
namespace console
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Iterator
>
class eval_grammar final
:
public
	boost::spirit::qi::grammar<
		Iterator,
		sge::console::arg_list()
	>
{
	FCPPT_NONCOPYABLE(
		eval_grammar
	);
public:
	eval_grammar();

	~eval_grammar();
private:
	boost::spirit::qi::rule<
		Iterator,
		sge::font::string()
	> word_;

	boost::spirit::qi::rule<
		Iterator,
		sge::font::string()
	> quoted_string_;

	boost::spirit::qi::rule<
		Iterator,
		sge::font::string()
	> argument_;

	boost::spirit::qi::rule<
		Iterator,
		sge::console::arg_list()
	> start_;
};

FCPPT_PP_POP_WARNING

}
}

#endif
