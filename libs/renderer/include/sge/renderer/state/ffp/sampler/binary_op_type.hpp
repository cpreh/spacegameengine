//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_FFP_SAMPLER_BINARY_OP_TYPE_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_SAMPLER_BINARY_OP_TYPE_HPP_INCLUDED

#include <sge/renderer/state/ffp/sampler/binary_op_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::state::ffp::sampler
{

enum class binary_op_type : std::uint8_t
{
  modulate,
  add,
  subtract,
  add_signed
};

}

#endif
