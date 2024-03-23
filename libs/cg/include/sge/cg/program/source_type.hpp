//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CG_PROGRAM_SOURCE_TYPE_HPP_INCLUDED
#define SGE_CG_PROGRAM_SOURCE_TYPE_HPP_INCLUDED

#include <sge/cg/program/source_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::cg::program
{

enum class source_type : std::uint8_t
{
  text,
  binary
};

}

#endif
