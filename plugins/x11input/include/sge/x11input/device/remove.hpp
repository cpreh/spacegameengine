//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_DEVICE_REMOVE_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_REMOVE_HPP_INCLUDED

#include <sge/input/exception.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/map.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/shared_ptr_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/find_opt_iterator.hpp>
#include <fcppt/optional/to_exception.hpp>

namespace sge::x11input::device
{

template <typename Type>
fcppt::shared_ptr<Type> remove(
    fcppt::reference<sge::x11input::device::map<Type>> const _map,
    sge::x11input::device::id const _id)
{
  using iterator_type = typename sge::x11input::device::map<Type>::iterator;

  iterator_type const iterator{fcppt::optional::to_exception(
      fcppt::container::find_opt_iterator(_map.get(), _id),
      [] { return sge::input::exception{FCPPT_TEXT("Unable to remove x11input device!")}; })};

  fcppt::shared_ptr<Type> result{iterator->second};

  _map.get().erase(iterator);

  return result;
}

}

#endif
