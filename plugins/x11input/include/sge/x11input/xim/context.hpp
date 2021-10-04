//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_XIM_CONTEXT_HPP_INCLUDED
#define SGE_X11INPUT_XIM_CONTEXT_HPP_INCLUDED

#include <sge/x11input/xim/context_fwd.hpp>
#include <awl/backends/x11/window/object_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>


namespace sge::x11input::xim
{

class context
{
	FCPPT_NONMOVABLE(
		context
	);
public:
	context(
		XIM,
		awl::backends::x11::window::object_ref
	);

	~context();

	[[nodiscard]]
	XIC
	get() const;
private:
	XIC const xic_; // NOLINT(misc-misplaced-const)
};

}

#endif
