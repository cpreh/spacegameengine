//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/x11input/xim/scoped_locale.hpp>
#include <sge/x11input/xim/setlocale.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


sge::x11input::xim::scoped_locale::scoped_locale(
	std::string const &_name
)
:
	old_locale_(
		sge::x11input::xim::setlocale(
			_name
		)
	)
{
}

sge::x11input::xim::scoped_locale::~scoped_locale()
{
	sge::x11input::xim::setlocale(
		old_locale_
	);
}
