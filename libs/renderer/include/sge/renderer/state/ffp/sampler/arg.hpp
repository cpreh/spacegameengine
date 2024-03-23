//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_FFP_SAMPLER_ARG_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_SAMPLER_ARG_HPP_INCLUDED

#include <sge/renderer/state/ffp/sampler/arg_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::state::ffp::sampler
{

enum class arg : std::uint8_t
{
  previous,
  texture,
  constant,
  vertex_color
};

}

#endif
