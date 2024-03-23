//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_ALGORITHM_UNINITIALIZED_HPP_INCLUDED
#define SGE_IMAGE_ALGORITHM_UNINITIALIZED_HPP_INCLUDED

#include <sge/image/algorithm/uninitialized_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::image::algorithm
{

enum class uninitialized : std::uint8_t
{
  no,
  yes
};

}

#endif
