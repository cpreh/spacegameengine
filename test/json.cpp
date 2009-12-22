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



#include <sge/parse/json/parse_stream.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/io/istringstream.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/next_prior.hpp>
#include <cstdlib>

#include <sge/parse/json/null.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/parse_stream.hpp>


namespace
{

template<
	typename T
>
void print(
	T const &t)
{
	fcppt::io::cout << t;
}

void print(
	sge::parse::json::null const &)
{
	fcppt::io::cout << FCPPT_TEXT("null");
}

void print(
	sge::parse::json::object const &obj);
void print(
	sge::parse::json::value const &obj);

void print(
	sge::parse::json::array const &a)
{
	fcppt::io::cout << FCPPT_TEXT('[');

	for(
		sge::parse::json::element_vector::const_iterator it(
			a.elements.begin()
		);
		it != a.elements.end();
		++it
	)
	{
		print(
			*it
		);

		if(
			boost::next(
				it
			)
			!= a.elements.end()
		)
			fcppt::io::cout << FCPPT_TEXT(',');
	}

	fcppt::io::cout << FCPPT_TEXT(']');
}

struct output_visitor : boost::static_visitor<> {
	template<
		typename T
	>
	void operator()(
		T const &t) const
	{
		print(t);
	}
};

void print(
	sge::parse::json::value const &val)
{
	boost::apply_visitor(
		output_visitor(),
		val
	);
}

void print(
	sge::parse::json::object const &obj)
{
	fcppt::io::cout << FCPPT_TEXT('{');

	for(
		sge::parse::json::member_vector::const_iterator it(
			obj.members.begin()
		);
		it != obj.members.end();
		++it
	)
	{
		fcppt::io::cout
			<< it->name
			<< FCPPT_TEXT(": ");

		print(
			it->value_
		);

		if(
			boost::next(
				it
			)
			!= obj.members.end()
		)
			fcppt::io::cout << FCPPT_TEXT(", ");
	}

	fcppt::io::cout << FCPPT_TEXT('}');
}

}

int main()
{
	fcppt::string const test(
		FCPPT_TEXT("{ \"foo\": 42, \"bar\" : { \"inner\" : 5.5 } }")
	);

	fcppt::io::istringstream
		ss(
			test
		);

	fcppt::string::const_iterator beg(
		test.begin()
	);

	sge::parse::json::object result;

	if(!sge::parse::json::parse_stream(
		ss,
		result
	))
	{
		fcppt::io::cerr << FCPPT_TEXT("failure\n");
		return EXIT_FAILURE;
	}

	print(
		result
	);

	fcppt::io::cout << FCPPT_TEXT('\n');
}
