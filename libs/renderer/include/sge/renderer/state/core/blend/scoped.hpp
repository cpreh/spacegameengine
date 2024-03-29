//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_CORE_BLEND_SCOPED_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_BLEND_SCOPED_HPP_INCLUDED

#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/blend/object_fwd.hpp>
#include <sge/renderer/state/core/blend/scoped_fwd.hpp> // IWYU pragma: keep
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_fwd.hpp>

namespace sge::renderer::state::core::blend
{

class scoped
{
  FCPPT_NONMOVABLE(scoped);

public:
  SGE_RENDERER_DETAIL_SYMBOL
  scoped(
      sge::renderer::context::core_ref,
      fcppt::reference<sge::renderer::state::core::blend::object const>);

  SGE_RENDERER_DETAIL_SYMBOL
  ~scoped();

private:
  sge::renderer::context::core_ref context_;
};

}

#endif
