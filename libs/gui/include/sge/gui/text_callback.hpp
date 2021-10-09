//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GUI_TEXT_CALLBACK_HPP_INCLUDED
#define SGE_GUI_TEXT_CALLBACK_HPP_INCLUDED

#include <sge/gui/text_function.hpp>
#include <fcppt/function_impl.hpp>

namespace sge::gui
{

using text_callback = fcppt::function<sge::gui::text_function>;

}

#endif
