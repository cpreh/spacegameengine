/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/parse/exception.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/find_member_value.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/string_to_value.hpp>
#include <sge/parse/json/config/command_line_parameters.hpp>
#include <sge/parse/json/config/help_needed_exception.hpp>
#include <sge/parse/json/config/merge_command_line_parameters.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/reference_wrapper_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/algorithm/shortest_levenshtein.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/spirit/include/qi_char.hpp>
#include <boost/spirit/include/qi_lit.hpp>
#include <boost/spirit/include/qi_operator.hpp>
#include <boost/spirit/include/qi_parse.hpp>
#include <boost/spirit/include/support_standard.hpp>
#include <iterator>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

void
process_option(
	sge::parse::json::object &_object,
	fcppt::string const &_input
)
{
	typedef
	std::vector<
		fcppt::string
	>
	string_vector;

	typedef
	boost::fusion::vector<
		string_vector,
		fcppt::string
	>
	result_type;

	namespace encoding = boost::spirit::standard;

	result_type result;

	if(
		!boost::spirit::qi::parse(
			_input.begin(),
			_input.end(),
			(
				*~encoding::char_("/=")
				% boost::spirit::lit('/')
			)
			>> boost::spirit::lit('=')
			>> *encoding::char_,
			result
		)
	)
		throw sge::parse::exception{
			FCPPT_TEXT("The command line parameter \"")
			+
			_input
			+
			FCPPT_TEXT("\" has an invalid format. See --help to see what that means.")
		};

	string_vector &first{
		boost::fusion::at_c<
			0
		>(
			result
		)
	};

	// If this is true, we have no left hand side of the '=' sign, which
	// cannot be!
	FCPPT_ASSERT_ERROR(
		!first.empty()
	);

	fcppt::string const element{
		first.back()
	};

	first.pop_back();

	typedef
	fcppt::reference_wrapper<
		sge::parse::json::object
	>
	object_ref;

	object_ref target{
		fcppt::algorithm::fold(
			first,
			fcppt::make_ref(
				_object
			),
			[](
				fcppt::string const &_value,
				object_ref const _cur
			)
			{
				return
					fcppt::make_ref(
						sge::parse::json::find_member_exn<
							sge::parse::json::object
						>(
							_cur.get().members,
							_value
						)
					);
			}
		)
	};

	typedef fcppt::optional<
		sge::parse::json::value &
	> optional_value;

	optional_value const pos(
		sge::parse::json::find_member_value(
			target.get().members,
			element
		)
	);

	if(
		!pos
	)
		throw sge::parse::exception{
			FCPPT_TEXT("Couldn't find member \"")
			+
			element
			+
			FCPPT_TEXT("\", did you mean: ")
			+
			fcppt::algorithm::shortest_levenshtein(
				fcppt::algorithm::map<
					string_vector
				>(
					target.get().members,
					[](
						sge::parse::json::member_map::value_type const &_element
					)
					{
						return
							_element.first;
					}
				),
				element
			)
		};

	*pos =
		sge::parse::json::string_to_value(
			boost::fusion::at_c<
				1
			>(
				result
			)
		);
}

}

sge::parse::json::object
sge::parse::json::config::merge_command_line_parameters(
	sge::parse::json::object input,
	sge::parse::json::config::command_line_parameters const &_parameters
)
{
	if(
		_parameters.size() >= 2
		&&
		_parameters[1] == FCPPT_TEXT("--help")
	)
	{
		fcppt::io::cout() <<
			FCPPT_TEXT(
			"Command line options are of the form:\n\n"
			"foo/bar/baz=qux\n\n"
			"where foo/bar/baz is a sequence of objects in the config.json file.\n"
			"qux can be any json type (strings, arrays, etc.)\n"
			"For example, if config.json looks like this:\n\n"
			"{ \"renderer\" : { \"screen_size\" : [640,480] } }\n\n"
			"You could change the resolution via:\n\n"
			"renderer/screen_size=[1024,768]\n\n"
			"Be aware of two things, though:\n"
			"1. You can use _any_ json type, so it's possible to write\n\n"
			"renderer/screen_size=1.0\n\n"
			"which, of course, makes no sense. Try to use the correct type.\n"
			"2. Be aware of your shell' special characters. For example, in bash\n"
			"to set a json string, you have to write:\n\n"
			"player/name='\"foobar\"'\n\n"
			"It's a good idea to always put the argument in apostrophes.\n"
			);
		throw
			sge::parse::json::config::help_needed_exception{
				FCPPT_TEXT("Help was needed")
			};
	}

	for(
		auto const &element
		:
		boost::make_iterator_range(
			std::next(
				_parameters.begin()
			),
			_parameters.end()
		)
	)
		::process_option(
			input,
			element
		);

	return
		input;
}
