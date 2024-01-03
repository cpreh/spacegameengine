//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_CONTEXT_SCOPED_OFFSCREEN_TARGET_HPP_INCLUDED
#define SGE_RENDERER_CONTEXT_SCOPED_OFFSCREEN_TARGET_HPP_INCLUDED

#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/context/scoped_offscreen_target_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/target/offscreen_ref.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::renderer::context
{

class scoped_offscreen_target
{
  FCPPT_NONMOVABLE(scoped_offscreen_target);

public:
  SGE_RENDERER_DETAIL_SYMBOL
  scoped_offscreen_target(sge::renderer::context::core_ref, sge::renderer::target::offscreen_ref);

  SGE_RENDERER_DETAIL_SYMBOL
  ~scoped_offscreen_target();

private:
  sge::renderer::context::core_ref const context_;
};

}

#endif
