//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_XIM_METHOD_UNIQUE_PTR_HPP_INCLUDED
#define SGE_X11INPUT_XIM_METHOD_UNIQUE_PTR_HPP_INCLUDED

#include <sge/x11input/xim/method_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace x11input
{
namespace xim
{

typedef
fcppt::unique_ptr<
	sge::x11input::xim::method
>
method_unique_ptr;

}
}
}

#endif
