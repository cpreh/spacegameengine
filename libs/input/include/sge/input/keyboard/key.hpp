//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_KEYBOARD_KEY_HPP_INCLUDED
#define SGE_INPUT_KEYBOARD_KEY_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/key/code.hpp>
#include <sge/input/keyboard/key_fwd.hpp>
#include <sge/input/keyboard/key_id.hpp>

namespace sge::input::keyboard
{

class key
{
public:
  SGE_INPUT_DETAIL_SYMBOL
  key(sge::input::key::code, sge::input::keyboard::key_id);

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::key::code code() const;

  [[nodiscard]] SGE_INPUT_DETAIL_SYMBOL sge::input::keyboard::key_id id() const;

private:
  sge::input::key::code code_;

  sge::input::keyboard::key_id id_;
};

SGE_INPUT_DETAIL_SYMBOL
bool operator==(sge::input::keyboard::key const &, sge::input::keyboard::key const &);

SGE_INPUT_DETAIL_SYMBOL
bool operator!=(sge::input::keyboard::key const &, sge::input::keyboard::key const &);

}

#endif
