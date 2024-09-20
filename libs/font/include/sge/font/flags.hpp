//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_FONT_FLAGS_HPP_INCLUDED
#define SGE_FONT_FLAGS_HPP_INCLUDED

#include <sge/font/flags_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::font
{

enum class flags : std::uint8_t
{
  no_multi_line,
  no_word_wrap
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sge::font::flags::no_word_wrap);

#endif
