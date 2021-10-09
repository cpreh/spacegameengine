//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/scenic/render_context/base.hpp>
#include <sge/scenic/render_context/base_unique_ptr.hpp>
#include <sge/scenic/render_context/ffp/manager.hpp>
#include <sge/scenic/render_context/ffp/object.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>

sge::scenic::render_context::ffp::manager::manager(
    sge::renderer::device::ffp_ref const _renderer,
    sge::renderer::vertex::const_declaration_ref const _vertex_declaration)
    : renderer_(_renderer), vertex_declaration_(_vertex_declaration)
{
}

sge::scenic::render_context::base_unique_ptr
sge::scenic::render_context::ffp::manager::create_context(
    sge::renderer::context::core_ref const _context)
{
  return fcppt::unique_ptr_to_base<sge::scenic::render_context::base>(
      fcppt::make_unique_ptr<sge::scenic::render_context::ffp::object>(
          fcppt::make_ref(*this),
          fcppt::make_ref(dynamic_cast<sge::renderer::context::ffp &>(_context.get()))));
}

sge::scenic::render_context::ffp::manager::~manager() = default;
