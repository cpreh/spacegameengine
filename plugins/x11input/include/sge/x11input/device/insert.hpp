//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_DEVICE_INSERT_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_INSERT_HPP_INCLUDED

#include <sge/input/exception.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/map.hpp>
#include <fcppt/not.hpp>
#include <fcppt/shared_ptr_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace sge::x11input::device
{

template <typename Type>
fcppt::shared_ptr<Type> insert(
    sge::x11input::device::map<Type> &_map,
    sge::x11input::device::id const _id,
    fcppt::shared_ptr<Type> _ptr)
{
  if(fcppt::not_(_map.insert(std::make_pair(_id, _ptr)).second))
  {
    throw sge::input::exception{FCPPT_TEXT("Double insert in x11input!")};
  }

  return _ptr;
}

}

#endif
