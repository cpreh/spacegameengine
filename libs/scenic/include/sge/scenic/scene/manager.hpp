//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_SCENE_MANAGER_HPP_INCLUDED
#define SGE_SCENIC_SCENE_MANAGER_HPP_INCLUDED

#include <sge/image2d/system_ref.hpp>
#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <sge/scenic/texture_manager.hpp>
#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/base_unique_ptr.hpp>
#include <sge/scenic/render_context/manager_base_unique_ptr.hpp>
#include <sge/scenic/scene/manager_fwd.hpp> // IWYU pragma: keep
#include <sge/scenic/scene/prefer_cg_context.hpp>
#include <sge/shader/context.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::scenic::scene
{

class manager
{
  FCPPT_NONMOVABLE(manager);

public:
  SGE_SCENIC_DETAIL_SYMBOL
  manager(
      sge::renderer::device::core_ref,
      sge::image2d::system_ref,
      sge::scenic::scene::prefer_cg_context const &);

  [[nodiscard]] SGE_SCENIC_DETAIL_SYMBOL sge::scenic::render_context::base_unique_ptr
      create_render_context(sge::renderer::context::core_ref);

  [[nodiscard]] SGE_SCENIC_DETAIL_SYMBOL sge::renderer::device::core &renderer() const;

  [[nodiscard]] SGE_SCENIC_DETAIL_SYMBOL sge::renderer::vertex::declaration &vertex_declaration();

  [[nodiscard]] SGE_SCENIC_DETAIL_SYMBOL sge::scenic::texture_manager &texture_manager();

  [[nodiscard]] SGE_SCENIC_DETAIL_SYMBOL sge::shader::context &shader_context();

  SGE_SCENIC_DETAIL_SYMBOL
  ~manager();

private:
  sge::renderer::device::core_ref const renderer_;
  sge::renderer::vertex::declaration_unique_ptr const mesh_vertex_declaration_;
  sge::scenic::texture_manager texture_manager_;
  sge::shader::context shader_context_;
  sge::scenic::render_context::manager_base_unique_ptr render_context_manager_;
};

}

#endif
