//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/x11input/atom_name.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/display_ref.hpp>
#include <awl/backends/x11/free.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>


sge::x11input::atom_name::atom_name(
	awl::backends::x11::display_ref const _display,
	Atom const _atom
)
:
	name_(
		::XGetAtomName(
			_display.get().get(),
			_atom
		)
	)
{
}

sge::x11input::atom_name::~atom_name()
{
	awl::backends::x11::free(
		name_
	);
}

char const *
sge::x11input::atom_name::get() const
{
	return
		name_;
}
