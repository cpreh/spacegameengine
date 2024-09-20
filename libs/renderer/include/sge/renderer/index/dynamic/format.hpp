//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_INDEX_DYNAMIC_FORMAT_HPP_INCLUDED
#define SGE_RENDERER_INDEX_DYNAMIC_FORMAT_HPP_INCLUDED

#include <sge/renderer/index/dynamic/format_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::index::dynamic
{

enum class format : std::uint8_t
{
  i16,
  i32
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sge::renderer::index::dynamic::format::i32);

#endif
