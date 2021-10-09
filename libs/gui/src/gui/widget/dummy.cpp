//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/dummy.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>

sge::gui::widget::dummy::dummy() : sge::gui::widget::base() {}

sge::gui::widget::dummy::~dummy() = default;

void sge::gui::widget::dummy::on_draw(sge::gui::renderer::base &, sge::renderer::context::ffp &) {}
