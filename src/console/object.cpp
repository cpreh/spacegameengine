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
#include <sge/parse/encoding.hpp>
#include <fcppt/auto_ptr.hpp>
#include <fcppt/make_auto_ptr.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/text.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
//#include <boost/spirit/include/phoenix_object.hpp>
//#include <boost/spirit/include/phoenix_stl.hpp>
#include <utility>

sge::console::object::object(
	fcppt::char_type const _prefix
)
:
	error_(),
	message_(),
	prefix_(
		_prefix),
	funcs_(),
	fallback_(),
	help_connection_(
		insert(
			FCPPT_TEXT("help"),
			std::tr1::bind(
				&object::help_callback,
				this,
				std::tr1::placeholders::_1),
			FCPPT_TEXT("Display help message"))),
	man_connection_(
		insert(
			FCPPT_TEXT("man"),
			std::tr1::bind(
				&object::man_callback,
				this,
				std::tr1::placeholders::_1),
			FCPPT_TEXT("Display information for a specific function")))
{
}

fcppt::signal::auto_connection
sge::console::object::insert(
	fcppt::string const &name,
	callback const &c,
	fcppt::string const &short_description,
	fcppt::string const &long_description
)
{
	function_map::iterator i = funcs_.find(name);
	if (i == funcs_.end())
	{
		fcppt::auto_ptr<function> sig(
			fcppt::make_auto_ptr<function>(
				short_description,
				long_description));

		std::pair<function_map::iterator,bool> const ret(
			funcs_.insert(
				name,
				sig));

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

fcppt::signal::auto_connection
sge::console::object::register_error_callback(
	error_callback const &c
)
{
	return error_.connect(c);
}

fcppt::signal::auto_connection
sge::console::object::register_message_callback(
	message_callback const &c
)
{
	return message_.connect(c);
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

	object::eval(
		args
	);
}

void
sge::console::object::eval(
	console::arg_list const &args
)
{
	// just typing the prefix is not an error
	if(
		args.empty()
	)
		return;

	function_map::iterator const it(
		funcs_.find(
			args[0]
		)
	);

	if (
		it == funcs_.end()
	)
		throw console::exception(
			FCPPT_TEXT("couldn't find command \"")
			+
			args[0]
			+
			FCPPT_TEXT('"')
		);

	it->second->signal()(
		args,
		std::tr1::ref(*this));
}

sge::console::function_map const &
sge::console::object::functions() const
{
	return funcs_;
}

fcppt::char_type
sge::console::object::prefix() const
{
	return prefix_;
}

void
sge::console::object::emit_error(
	fcppt::string const &s)
{
	error_(
		s);
}

void
sge::console::object::emit_message(
	fcppt::string const &s)
{
	message_(
		s);
}

void
sge::console::object::help_callback(
	arg_list const &)
{
	emit_message(
		fcppt::lexical_cast<fcppt::string>( 
			funcs_.size())
		+ FCPPT_TEXT(" available functions:"));

	BOOST_FOREACH(function_map::value_type const &p,funcs_)
		emit_message(
			(p->first)+
			FCPPT_TEXT(": ")+
			(p.second)->short_description());
}

void
sge::console::object::man_callback(
	arg_list const &v)
{
	if (v.size() < 2)
	{
		emit_error(
			FCPPT_TEXT("no function given"));
		return;
	}

	function_map const &fns = 
		funcs_;

	function_map::const_iterator i = 
		funcs_.find(
			v[1]);

	if (i == fns.end())
	{
		emit_error(
			FCPPT_TEXT("function \"")+v[1]+FCPPT_TEXT("\" not found"));
		return;
	}

	if (i->second->long_description().empty())
		emit_message(
			FCPPT_TEXT("No manpage available"));
	else	
		emit_message(
			i->second->long_description());
}
