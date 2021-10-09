//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_RENDER_CONTEXT_BASE_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_BASE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/index/buffer_fwd.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/scenic/index_buffer_range_fwd.hpp>
#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/transform_matrix_type_fwd.hpp>
#include <sge/scenic/render_context/fog/optional_properties.hpp>
#include <sge/scenic/render_context/light/sequence.hpp>
#include <sge/scenic/render_context/material/object_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::scenic::render_context
{

class SGE_CORE_DETAIL_CLASS_SYMBOL base
{
  FCPPT_NONMOVABLE(base);

public:
  virtual void
  transform(sge::scenic::render_context::transform_matrix_type, sge::renderer::matrix4 const &) = 0;

  virtual void material(sge::scenic::render_context::material::object const &) = 0;

  virtual void lights(sge::scenic::render_context::light::sequence const &) = 0;

  virtual void vertex_buffer(sge::renderer::vertex::buffer const &) = 0;

  virtual void fog(sge::scenic::render_context::fog::optional_properties const &) = 0;

  virtual void
  render(sge::renderer::index::buffer const &, sge::scenic::index_buffer_range const &) = 0;

  virtual sge::renderer::target::base &target() = 0;

  virtual ~base();

protected:
  base();
};

}

#endif
