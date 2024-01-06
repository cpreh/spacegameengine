//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_RENDER_CONTEXT_FFP_MANAGER_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_FFP_MANAGER_HPP_INCLUDED

#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/base_unique_ptr.hpp>
#include <sge/scenic/render_context/manager_base.hpp>
#include <sge/scenic/render_context/ffp/object_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::scenic::render_context::ffp
{

class manager : public sge::scenic::render_context::manager_base
{
  FCPPT_NONMOVABLE(manager);

public:
  SGE_SCENIC_DETAIL_SYMBOL
  manager(sge::renderer::device::ffp_ref, sge::renderer::vertex::const_declaration_ref);

  [[nodiscard]] SGE_SCENIC_DETAIL_SYMBOL sge::scenic::render_context::base_unique_ptr
      create_context(sge::renderer::context::core_ref) override;

  SGE_SCENIC_DETAIL_SYMBOL
  ~manager() override;

private:
  friend class sge::scenic::render_context::ffp::object;

  sge::renderer::device::ffp_ref const renderer_;

  sge::renderer::vertex::const_declaration_ref const vertex_declaration_;
};

}

#endif
