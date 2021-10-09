//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SDLINPUT_TRANSLATE_PRESSED_HPP_INCLUDED
#define SGE_SDLINPUT_TRANSLATE_PRESSED_HPP_INCLUDED

#include <sge/sdlinput/translate/pressed_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::sdlinput::translate
{

template <typename Event>
bool pressed(Event const &_event)
{
  return sge::sdlinput::translate::pressed_impl(_event.state);
}

}

#endif
