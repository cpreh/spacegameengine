//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_RENDER_CONTEXT_MANAGER_BASE_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_MANAGER_BASE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/context/core_ref.hpp>
#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/base_unique_ptr.hpp>
#include <sge/scenic/render_context/manager_base_fwd.hpp> // IWYU pragma: keep
#include <fcppt/nonmovable.hpp>

namespace sge::scenic::render_context
{

class SGE_CORE_DETAIL_CLASS_SYMBOL manager_base
{
  FCPPT_NONMOVABLE(manager_base);

public:
  [[nodiscard]] virtual sge::scenic::render_context::base_unique_ptr
      create_context(sge::renderer::context::core_ref) = 0;

  SGE_SCENIC_DETAIL_SYMBOL virtual ~manager_base();

protected:
  manager_base();
};

}

#endif
