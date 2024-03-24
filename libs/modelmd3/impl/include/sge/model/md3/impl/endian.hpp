//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_MODEL_MD3_IMPL_ENDIAN_HPP_INCLUDED
#define SGE_MODEL_MD3_IMPL_ENDIAN_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <bit>
#include <fcppt/config/external_end.hpp>

namespace sge::model::md3::impl
{

constexpr std::endian endian() { return std::endian::little; }

}

#endif
