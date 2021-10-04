//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WLINPUT_XKB_CONTEXT_REF_HPP_INCLUDED
#define SGE_WLINPUT_XKB_CONTEXT_REF_HPP_INCLUDED

#include <sge/wlinput/xkb_context_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge::wlinput
{

using
xkb_context_ref
=
fcppt::reference<
	sge::wlinput::xkb_context
>;

}

#endif
