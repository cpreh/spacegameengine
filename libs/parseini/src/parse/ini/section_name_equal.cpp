//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/section_name.hpp>
#include <sge/parse/ini/section_name_equal.hpp>


sge::parse::ini::section_name_equal::section_name_equal(
	sge::parse::ini::section_name const &_name
)
:
	name_(
		_name
	)
{
}

sge::parse::ini::section_name_equal::result_type
sge::parse::ini::section_name_equal::operator()(
	sge::parse::ini::section const &_section
) const
{
	return
		_section.name == name_.get();
}
