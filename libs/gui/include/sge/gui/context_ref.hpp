//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GUI_CONTEXT_REF_HPP_INCLUDED
#define SGE_GUI_CONTEXT_REF_HPP_INCLUDED

#include <sge/gui/context_fwd.hpp>
#include <fcppt/reference_impl.hpp>

namespace sge::gui
{

using context_ref = fcppt::reference<sge::gui::context>;

}

#endif
