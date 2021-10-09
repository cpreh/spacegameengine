//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/gui/main_area/base.hpp>
#include <sge/gui/main_area/viewport_adaptor.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/make_ref.hpp>

sge::gui::main_area::viewport_adaptor::viewport_adaptor(
    sge::renderer::device::core_ref const _device,
    sge::viewport::manager_ref const _viewport_manager,
    sge::gui::widget::reference const _widget)
    : sge::gui::main_area::base(), widget_(_widget), impl_(_viewport_manager, _device)
{
  impl_.child(fcppt::make_ref(_widget.get().layout()));

  impl_.relayout();
}

sge::gui::main_area::viewport_adaptor::~viewport_adaptor() = default;

void sge::gui::main_area::viewport_adaptor::relayout() { impl_.relayout(); }

sge::gui::widget::base &sge::gui::main_area::viewport_adaptor::widget() { return widget_.get(); }
