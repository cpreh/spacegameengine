//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_JOYPAD_BUTTON_INFO_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_BUTTON_INFO_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/joypad/button_info_fwd.hpp>
#include <fcppt/optional_string.hpp>

namespace sge::input::joypad
{

class button_info
{
public:
  SGE_INPUT_DETAIL_SYMBOL
  explicit button_info(fcppt::optional_string &&);

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL fcppt::optional_string const &name() const;

private:
  fcppt::optional_string name_;
};

}

#endif
