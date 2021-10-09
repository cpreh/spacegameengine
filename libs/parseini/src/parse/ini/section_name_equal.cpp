//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/section_name.hpp>
#include <sge/parse/ini/section_name_equal.hpp>
#include <fcppt/reference_impl.hpp>

sge::parse::ini::section_name_equal::section_name_equal(
    fcppt::reference<sge::parse::ini::section_name const> const _name)
    : name_{_name}
{
}

bool sge::parse::ini::section_name_equal::operator()(sge::parse::ini::section const &_section) const
{
  return _section.name == this->name_.get().get();
}
