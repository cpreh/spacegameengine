//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/viewport/adaptor.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/optional_ref.hpp>
#include <sge/rucksack/widget/reference.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/comparison.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::rucksack::viewport::adaptor::adaptor(
    sge::viewport::manager_ref const _viewport_manager,
    sge::renderer::device::core_ref const _renderer)
    : sge::rucksack::widget::base(),
      target_(_renderer.get().onscreen_target()),
      child_(),
      viewport_connection_(_viewport_manager.get().manage_callback(sge::viewport::manage_callback{
          [this](sge::renderer::target::viewport const &)
          { this->sge::rucksack::viewport::adaptor::manage_callback(); }}))
{
}

FCPPT_PP_POP_WARNING

void sge::rucksack::viewport::adaptor::size(sge::rucksack::dim const &_size)
{
  target_.viewport(sge::renderer::target::viewport(sge::renderer::pixel_rect(
      target_.viewport().get().pos(),
      fcppt::math::dim::structure_cast<sge::renderer::pixel_rect::dim, fcppt::cast::size_fun>(
          _size))));
}

void sge::rucksack::viewport::adaptor::position(sge::rucksack::vector const &_pos)
{
  target_.viewport(sge::renderer::target::viewport(sge::renderer::pixel_rect(
      fcppt::math::vector::structure_cast<sge::renderer::pixel_rect::vector, fcppt::cast::size_fun>(
          _pos),
      target_.viewport().get().size())));
}

sge::rucksack::dim sge::rucksack::viewport::adaptor::size() const
{
  return fcppt::math::dim::structure_cast<sge::rucksack::dim, fcppt::cast::size_fun>(
      target_.viewport().get().size());
}

sge::rucksack::vector sge::rucksack::viewport::adaptor::position() const
{
  return fcppt::math::vector::structure_cast<sge::rucksack::vector, fcppt::cast::size_fun>(
      target_.viewport().get().pos());
}

sge::rucksack::axis_policy2 sge::rucksack::viewport::adaptor::axis_policy() const
{
  // A dummy for now, until there's a use case
  return sge::rucksack::axis_policy2{
      sge::rucksack::axis_policy{sge::rucksack::minimum_size{sge::rucksack::scalar()}},
      sge::rucksack::axis_policy{sge::rucksack::minimum_size{sge::rucksack::scalar()}}};
}

void sge::rucksack::viewport::adaptor::relayout()
{
  fcppt::optional::maybe_void(
      child_,
      [this](fcppt::reference<sge::rucksack::widget::base> const _child)
      {
        this->resize_child();

        _child.get().relayout();
      });
}

void sge::rucksack::viewport::adaptor::child(sge::rucksack::widget::reference const _new_child)
{
  fcppt::optional::maybe_void(
      child_,
      [](fcppt::reference<sge::rucksack::widget::base> const _child)
      { _child.get().parent(sge::rucksack::widget::optional_ref()); });

  child_ = sge::rucksack::widget::optional_ref(_new_child);

  _new_child.get().parent(sge::rucksack::widget::optional_ref(
      fcppt::reference_to_base<sge::rucksack::widget::base>(fcppt::make_ref(*this))));

  this->resize_child();
}

sge::rucksack::viewport::adaptor::~adaptor()
{
  fcppt::optional::maybe_void(
      child_,
      [](fcppt::reference<sge::rucksack::widget::base> const _child)
      { _child.get().parent(sge::rucksack::widget::optional_ref()); });
}

void sge::rucksack::viewport::adaptor::manage_callback()
{
  if (child_.has_value())
  {
    this->resize_child();
  }
}

void sge::rucksack::viewport::adaptor::resize_child()
{
  fcppt::optional::maybe_void(
      this->child_,
      [this](fcppt::reference<sge::rucksack::widget::base> const _child)
      {
        _child->position(fcppt::math::vector::null<sge::rucksack::vector>());

        _child->size(this->size());

        _child->relayout();
      });
}

void sge::rucksack::viewport::adaptor::child_destroyed(sge::rucksack::widget::base &)
{
  child_ = sge::rucksack::widget::optional_ref();
}
