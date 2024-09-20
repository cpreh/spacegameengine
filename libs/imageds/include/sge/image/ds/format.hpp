//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_DS_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_DS_FORMAT_HPP_INCLUDED

#include <sge/image/ds/format_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::image::ds
{

enum class format : std::uint8_t
{
  d16,
  d32,
  d24s8
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sge::image::ds::format::d24s8);

#endif
