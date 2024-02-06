//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image2d/system_ref.hpp>
#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/scenic/texture_manager.hpp>
#include <sge/scenic/render_context/base.hpp> // NOLINT(misc-include-cleaner)
#include <sge/scenic/render_context/base_unique_ptr.hpp>
#include <sge/scenic/render_context/manager_base.hpp>
#include <sge/scenic/render_context/cg/manager.hpp>
#include <sge/scenic/render_context/ffp/manager.hpp>
#include <sge/scenic/scene/manager.hpp>
#include <sge/scenic/scene/prefer_cg_context.hpp>
#include <sge/scenic/vf/format.hpp>
#include <sge/shader/context.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>

sge::scenic::scene::manager::manager(
    sge::renderer::device::core_ref const _renderer,
    sge::image2d::system_ref const _image_loader,
    sge::scenic::scene::prefer_cg_context const &_prefer_cg_context)
    : renderer_(_renderer),
      mesh_vertex_declaration_(
          renderer_.get().create_vertex_declaration(sge::renderer::vertex::declaration_parameters(
              sge::renderer::vf::dynamic::make_format<sge::scenic::vf::format>()))),
      texture_manager_(renderer_, _image_loader),
      shader_context_(renderer_),
      render_context_manager_(
          _prefer_cg_context.get()
              ? fcppt::unique_ptr_to_base<sge::scenic::render_context::manager_base>(
                    fcppt::make_unique_ptr<sge::scenic::render_context::cg::manager>(
                        fcppt::make_ref(shader_context_),
                        fcppt::make_cref(*mesh_vertex_declaration_)))
              : fcppt::unique_ptr_to_base<sge::scenic::render_context::manager_base>(
                    fcppt::make_unique_ptr<sge::scenic::render_context::ffp::manager>(
                        fcppt::make_ref(
                            dynamic_cast<sge::renderer::device::ffp &>(_renderer.get())),
                        fcppt::make_cref(*mesh_vertex_declaration_))))
{
}

sge::scenic::render_context::base_unique_ptr
sge::scenic::scene::manager::create_render_context(sge::renderer::context::core_ref const _context)
{
  return render_context_manager_->create_context(_context);
}

sge::renderer::device::core &sge::scenic::scene::manager::renderer() const
{
  return renderer_.get();
}

sge::renderer::vertex::declaration &sge::scenic::scene::manager::vertex_declaration()
{
  return *mesh_vertex_declaration_;
}

sge::scenic::texture_manager &sge::scenic::scene::manager::texture_manager()
{
  return texture_manager_;
}

sge::shader::context &sge::scenic::scene::manager::shader_context() { return shader_context_; }

sge::scenic::scene::manager::~manager() = default;
