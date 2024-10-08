//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_MODEL_MD3_LOAD_FLAGS_HPP_INCLUDED
#define SGE_MODEL_MD3_LOAD_FLAGS_HPP_INCLUDED

#include <sge/model/md3/load_flags_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::model::md3
{

enum class load_flags : std::uint8_t
{
  switch_yz
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sge::model::md3::load_flags::switch_yz);

#endif
