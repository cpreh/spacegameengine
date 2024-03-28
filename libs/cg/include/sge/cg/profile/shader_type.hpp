//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CG_PROFILE_SHADER_TYPE_HPP_INCLUDED
#define SGE_CG_PROFILE_SHADER_TYPE_HPP_INCLUDED

#include <sge/cg/profile/shader_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::cg::profile
{

enum class shader_type : std::uint8_t
{
  vertex,
  pixel,
  geometry
};

}

#endif
