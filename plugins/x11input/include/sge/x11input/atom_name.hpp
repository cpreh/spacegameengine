//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_ATOM_NAME_HPP_INCLUDED
#define SGE_X11INPUT_ATOM_NAME_HPP_INCLUDED

#include <awl/backends/x11/display_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>


namespace sge::x11input
{

class atom_name
{
	FCPPT_NONMOVABLE(
		atom_name
	);
public:
	atom_name(
		awl::backends::x11::display_ref,
		Atom
	);

	~atom_name();

	[[nodiscard]]
	char const *
	get() const;
private:
	char *const name_;
};

}

#endif
