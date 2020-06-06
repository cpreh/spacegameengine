//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/get_or_create.hpp>
#include <sge/parse/ini/get_or_create_entry.hpp>
#include <sge/parse/ini/get_or_create_section.hpp>
#include <sge/parse/ini/section_name.hpp>
#include <sge/parse/ini/start_fwd.hpp>
#include <sge/parse/ini/value.hpp>
#include <fcppt/reference_impl.hpp>


sge::parse::ini::value
sge::parse::ini::get_or_create(
	fcppt::reference<
		sge::parse::ini::start
	> const _start,
	sge::parse::ini::section_name const &_section_name,
	sge::parse::ini::entry_name const &_entry_name,
	sge::parse::ini::value const &_value
)
{
	return
		sge::parse::ini::value(
			sge::parse::ini::get_or_create_entry(
				sge::parse::ini::get_or_create_section(
					_start,
					_section_name
				),
				_entry_name,
				_value
			).get().value
		);
}
