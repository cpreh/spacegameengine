//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_XIM_METHOD_HPP_INCLUDED
#define SGE_X11INPUT_XIM_METHOD_HPP_INCLUDED

#include <sge/x11input/xim/method_fwd.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace xim
{

class method
{
	FCPPT_NONCOPYABLE(
		method
	);
public:
	explicit
	method(
		awl::backends::x11::display const &
	);

	~method();

	XIM
	get() const;
private:
	XIM const xim_;
};

}
}
}

#endif
