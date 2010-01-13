/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/console/object.hpp>
#include <sge/console/exception.hpp>
#include <sge/console/function.hpp>
#include <sge/console/var_base.hpp>
#include <sge/parse/encoding.hpp>
#include <fcppt/auto_ptr.hpp>
#include <fcppt/make_auto_ptr.hpp>
#include <fcppt/assert.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
//#include <boost/spirit/include/phoenix_object.hpp>
//#include <boost/spirit/include/phoenix_stl.hpp>
#include <utility>

sge::console::object::object(
	fcppt::char_type const _prefix
)
:
	prefix_(_prefix)
{
}

fcppt::signal::auto_connection
sge::console::object::insert(
	fcppt::string const &name,
	callback const &c,
	fcppt::string const &description
)
{
	function_map::iterator i = funcs_.find(name);
	if (i == funcs_.end())
	{
		fcppt::auto_ptr<
			function
		> sig(
			fcppt::make_auto_ptr<
				function
			>(description)
		);

		std::pair<function_map::iterator,bool> const ret(
			funcs_.insert(
				name,
				sig
			)
		);

		i = ret.first;
		FCPPT_ASSERT(ret.second);
	}
	return i->second->signal().connect(c);
}

fcppt::signal::auto_connection
sge::console::object::register_fallback(
	fallback const &c
)
{
	return fallback_.connect(c);
}

namespace
{
template <typename Iterator>
class eval_grammar : public boost::spirit::qi::grammar<
	Iterator,
	sge::console::arg_list()>
{
public:
	eval_grammar() : eval_grammar::base_type(start)
	{
		using sge::parse::encoding::char_;
		using sge::parse::encoding::space;

		word  %=           +(char_ - space);
		quoted_string %=   FCPPT_TEXT('"') >> +(char_ - FCPPT_TEXT('"')) >> FCPPT_TEXT('"');
		argument %=        quoted_string | word;
		start %=           argument % (+space);
	}

	boost::spirit::qi::rule<Iterator, fcppt::string()> word;
	boost::spirit::qi::rule<Iterator, fcppt::string()> quoted_string;
	boost::spirit::qi::rule<Iterator, fcppt::string()> argument;
	boost::spirit::qi::rule<Iterator, sge::console::arg_list()> start;
};
}

void
sge::console::object::eval(
	fcppt::string const &sp
)
{
	if (sp.empty())
		return;

	if (sp[0] != prefix_)
	{
		fallback_(sp);
		return;
	}

	fcppt::string const s = sp.substr(1);

	arg_list args;

	eval_grammar<
		fcppt::string::const_iterator
	> grammar;

	fcppt::string::const_iterator beg = s.begin();

	boost::spirit::qi::parse(
		beg,
		s.end(),
		grammar,
		args
	);

	function_map::iterator i = funcs_.find(args[0]);

	if (i == funcs_.end())
		throw exception(FCPPT_TEXT("couldn't find command \"")+args[0]+FCPPT_TEXT("\""));

	i->second->signal()(args);
}

sge::console::variable_map const &
sge::console::object::variables() const
{
	return vars_;
}

sge::console::variable_map &
sge::console::object::variables()
{
	return vars_;
}

sge::console::function_map const &
sge::console::object::functions() const
{
	return funcs_;
}

void
sge::console::object::insert(
	var_base &o
)
{
	vars_[o.name()] = &o;
}

void
sge::console::object::erase(
	var_base &o
)
{
	FCPPT_ASSERT(vars_.erase(o.name()) > 0);
}
