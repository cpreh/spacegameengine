/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/model/obj/exception.hpp>
#include <sge/src/model/obj/base_iterator.hpp>
#include <sge/src/model/obj/grammar.hpp>
#include <sge/src/model/obj/iterator.hpp>
#include <sge/src/model/obj/parse.hpp>
#include <sge/src/model/obj/parse_state_fwd.hpp>
#include <sge/src/model/obj/tokens.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/ifstream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/home/lex/qi/in_state.hpp>
#include <boost/spirit/home/qi/parse.hpp>
#include <fcppt/config/external_end.hpp>


void
sge::model::obj::parse(
	obj::tokens const &_tokens,
	fcppt::filesystem::path const &_path,
	obj::parse_state &_state
)
{
	fcppt::io::ifstream stream(
		_path
	);

	if(
		!stream.is_open()
	)
		throw sge::model::obj::exception(
			FCPPT_TEXT("Cannot open ")
			+
			fcppt::filesystem::path_to_string(
				_path
			)
		);

	stream.unsetf(
		std::ios_base::skipws
	);

	obj::base_iterator base_begin(
		stream
	);

	obj::iterator iter(
		_tokens.begin(
			base_begin,
			base_iterator()
		)
	);

	obj::iterator const end(
		_tokens.end()
	);

	obj::grammar grammar(
		_tokens,
		_state
	);

	if(
		!boost::spirit::qi::phrase_parse(
			iter,
			end,
			grammar,
			boost::spirit::qi::in_state(
				FCPPT_TEXT("WS")
			)[
				_tokens.self
			]
		)
		||
		iter != end
	)
		throw sge::model::obj::exception(
			FCPPT_TEXT("Unable to parse ")
			+
			fcppt::filesystem::path_to_string(
				_path
			)
		);
}
