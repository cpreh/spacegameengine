//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/entry_name_equal.hpp>
#include <fcppt/reference_impl.hpp>


sge::parse::ini::entry_name_equal::entry_name_equal(
	fcppt::reference<
		sge::parse::ini::entry_name const
	> const _name
)
:
	name_(
		_name
	)
{
}

bool
sge::parse::ini::entry_name_equal::operator()(
	sge::parse::ini::entry const &_entry
) const
{
	return
		_entry.name
		==
		this->name_.get().get();
}
