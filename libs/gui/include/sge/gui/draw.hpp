//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_DRAW_HPP_INCLUDED
#define SGE_GUI_DRAW_HPP_INCLUDED

#include <sge/gui/background/base_fwd.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/main_area/base_fwd.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>


namespace sge::gui
{

SGE_GUI_DETAIL_SYMBOL
void
draw(
	sge::gui::renderer::base &, // NOLINT(google-runtime-references)
	sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
	sge::gui::background::base &, // NOLINT(google-runtime-references)
	sge::gui::main_area::base & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

}

#endif
