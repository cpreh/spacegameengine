//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GUI_RENDERER_CREATE_SCOPED_HPP_INCLUDED
#define SGE_GUI_RENDERER_CREATE_SCOPED_HPP_INCLUDED

#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/renderer/base_unique_ptr.hpp>
#include <sge/renderer/context/ffp_ref.hpp>
#include <sge/renderer/device/ffp_ref.hpp>

namespace sge::gui::renderer
{

SGE_GUI_DETAIL_SYMBOL
sge::gui::renderer::base_unique_ptr
    create_scoped(sge::renderer::device::ffp_ref, sge::renderer::context::ffp_ref);

}

#endif
