//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_XIM_CONST_OPTIONAL_METHOD_REF_FWD_HPP_INCLUDED
#define SGE_X11INPUT_XIM_CONST_OPTIONAL_METHOD_REF_FWD_HPP_INCLUDED

#include <sge/x11input/xim/method_fwd.hpp>
#include <fcppt/optional/reference_fwd.hpp>


namespace sge
{
namespace x11input
{
namespace xim
{

using
const_optional_method_ref
=
fcppt::optional::reference<
	sge::x11input::xim::method const
>;

}
}
}

#endif
