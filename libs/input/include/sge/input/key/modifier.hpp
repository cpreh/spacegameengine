//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_KEY_MODIFIER_HPP_INCLUDED
#define SGE_INPUT_KEY_MODIFIER_HPP_INCLUDED

#include <sge/input/key/modifier_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::input::key
{

enum class modifier : std::uint8_t
{
  control,
  alt,
  shift
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sge::input::key::modifier::shift);

#endif
