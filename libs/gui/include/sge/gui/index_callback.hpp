//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_INDEX_CALLBACK_HPP_INCLUDED
#define SGE_GUI_INDEX_CALLBACK_HPP_INCLUDED

#include <sge/gui/index_function.hpp>
#include <fcppt/function_impl.hpp>


namespace sge::gui
{

using
index_callback
=
fcppt::function<
	sge::gui::index_function
>;

}

#endif
