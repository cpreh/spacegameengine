//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/context/core.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref_map.hpp>
#include <sge/renderer/state/core/sampler/single.hpp>
#include <sge/renderer/texture/stage.hpp>

void sge::renderer::state::core::sampler::single(
    sge::renderer::context::core_ref const _context,
    sge::renderer::texture::stage const _stage,
    sge::renderer::state::core::sampler::const_optional_object_ref const &_object)
{
  _context.get().sampler_state(sge::renderer::state::core::sampler::const_optional_object_ref_map{
      sge::renderer::state::core::sampler::const_optional_object_ref_map::value_type{
          _stage, _object}});
}
