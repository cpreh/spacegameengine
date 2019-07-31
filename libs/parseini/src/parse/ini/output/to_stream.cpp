//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/start.hpp>
#include <sge/parse/ini/output/to_stream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


void
sge::parse::ini::output::to_stream(
	std::ostream &_stream,
	sge::parse::ini::start const &_result
)
{
	for(
		sge::parse::ini::section const &section
		:
		_result.sections
	)
	{
		_stream
			<< '['
			<< section.name
			<< ']'
			<< '\n';

		for(
			sge::parse::ini::entry const &entry
			:
			section.entries
		)
			_stream
				<< '\t'
				<< entry.name
				<< '='
				<< entry.value
				<< '\n';
	}
}
