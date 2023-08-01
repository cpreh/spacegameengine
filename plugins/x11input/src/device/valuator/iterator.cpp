//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/x11input/mask_is_set.hpp>
#include <sge/x11input/device/valuator/index.hpp>
#include <sge/x11input/device/valuator/iterator.hpp>
#include <sge/x11input/device/valuator/iterator_base.hpp>
#include <sge/x11input/device/valuator/length.hpp>
#include <sge/x11input/device/valuator/pair.hpp>
#include <sge/x11input/device/valuator/value.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

sge::x11input::device::valuator::iterator::iterator(
    sge::x11input::device::valuator::index const _index, XIValuatorState const &_state)
    : sge::x11input::device::valuator::iterator_base{},
      state_{_state},
      valuator_{_state.values},
      index_{_index},
      length_{sge::x11input::device::valuator::length(_state)}
{
  this->index_to_next_valuator();
}

void sge::x11input::device::valuator::iterator::increment()
{
  ++index_;

  ++valuator_; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

  this->index_to_next_valuator();
}

bool sge::x11input::device::valuator::iterator::equal(iterator const &_other) const
{
  return index_ == _other.index_;
}

sge::x11input::device::valuator::iterator::reference
sge::x11input::device::valuator::iterator::dereference() const
{
  return sge::x11input::device::valuator::pair{
      index_, sge::x11input::device::valuator::value{*valuator_}};
}

void sge::x11input::device::valuator::iterator::index_to_next_valuator()
{
  for (; index_ != length_; ++index_)
  {
    if (sge::x11input::mask_is_set(state_.get().mask, index_.get()))
    {
      return;
    }
  }
}

FCPPT_PP_POP_WARNING
