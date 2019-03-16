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


#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <sge/parse/exception.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/find_member_value.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/string_to_value.hpp>
#include <sge/parse/json/config/help_needed_exception.hpp>
#include <sge/parse/json/config/merge_command_line_parameters.hpp>
#include <sge/parse/json/detail/to_fcppt_string.hpp>
#include <fcppt/args_vector.hpp>
#include <fcppt/char_type.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/algorithm/join_strings.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/compiler.hpp>
#include <fcppt/container/maybe_front.hpp>
#include <fcppt/either/to_exception.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/parse/basic_char.hpp>
#include <fcppt/parse/basic_char_set.hpp>
#include <fcppt/parse/basic_literal.hpp>
#include <fcppt/parse/epsilon.hpp>
#include <fcppt/parse/error.hpp>
#include <fcppt/parse/separator.hpp>
#include <fcppt/parse/parse_string.hpp>
#include <fcppt/parse/operators/complement.hpp>
#include <fcppt/parse/operators/repetition.hpp>
#include <fcppt/parse/operators/sequence.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tuple>
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
	std::tuple<
		string_vector,
		fcppt::string
	>
	result_type;

	typedef
	fcppt::parse::basic_char_set<
		fcppt::char_type
	>
	char_set;

	typedef
	fcppt::parse::basic_char<
		fcppt::char_type
	>
	char_;

	typedef
	fcppt::parse::basic_literal<
		fcppt::char_type
	>
	literal;

	result_type result{
		fcppt::either::to_exception(
			fcppt::parse::parse_string(
				fcppt::parse::separator{
					*~char_set{FCPPT_TEXT('/'),FCPPT_TEXT('=')},
					literal{FCPPT_TEXT('/')}
				}
				>>
				literal{FCPPT_TEXT('=')}
				>>
				*char_{},
				fcppt::string{
					_input
				},
				fcppt::parse::epsilon{}
			),
			[
				&_input
			](
				fcppt::parse::error<
					fcppt::char_type
				> &&_error
			)
			{
				return
					sge::parse::exception{
						FCPPT_TEXT("The command line parameter \"")
						+
						_input
						+
						FCPPT_TEXT("\" has an invalid format. See --help. The error is: ")
						+
						std::move(
							_error.get()
						)
					};
			}
		)
	};

	string_vector &first(
		std::get<
			0
		>(
			result
		)
	);

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
	fcppt::reference<
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
							sge::charconv::fcppt_string_to_utf8(
								_value
							)
						)
					);
			}
		)
	};

	fcppt::optional::to_exception(
		sge::parse::json::find_member_value(
			target.get().members,
			sge::charconv::fcppt_string_to_utf8(
				element
			)
		),
		[
			&target,
			&element
		]{
			return
				sge::parse::exception{
					FCPPT_TEXT("Couldn't find member \"")
					+
					element
					+
					FCPPT_TEXT("\", available members are: ")
					+
					fcppt::algorithm::join_strings(
						fcppt::algorithm::map<
							string_vector
						>(
							target.get().members,
							[](
								sge::parse::json::member const &_element
							)
							->
							fcppt::string
							{
								return
									sge::parse::json::detail::to_fcppt_string(
										_element.first
									);
							}
						),
						FCPPT_TEXT(", ")
					)
				};
		}
	).get() =
		sge::parse::json::string_to_value(
			sge::charconv::fcppt_string_to_utf8(
				std::get<
					1
				>(
					result
				)
			)
		);
}

}

sge::parse::json::object
sge::parse::json::config::merge_command_line_parameters(
	sge::parse::json::object input,
	fcppt::args_vector const &_parameters
)
{
	fcppt::optional::maybe_void(
		fcppt::container::maybe_front(
			_parameters
		),
		[](
			fcppt::reference<
				fcppt::string const
			> const _arg
		)
		{
			if(
				_arg.get()
				==
				FCPPT_TEXT("--help")
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
		}
	);

	for(
		auto const &element
		:
		_parameters
	)
		::process_option(
			input,
			element
		);

	return
		input;
}
