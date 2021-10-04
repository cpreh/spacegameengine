//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WINDOW_SYSTEM_REF_HPP_INCLUDED
#define SGE_WINDOW_SYSTEM_REF_HPP_INCLUDED

#include <sge/window/system_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge::window
{

using
system_ref
=
fcppt::reference<
	sge::window::system
>;

}

#endif
