//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cg/program/replace_extra.hpp>
#include <sge/cg/program/replace_extra_callback.hpp>
#include <sge/cg/program/source.hpp>
#include <sge/d3d9/vertex_declaration.hpp>
#include <sge/d3d9/cg/program/replace_index.hpp>
#include <sge/d3d9/cg/program/transform_vertex.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>

sge::cg::program::source const sge::d3d9::cg::program::transform_vertex(
    sge::renderer::vertex::declaration const &_vertex_declaration,
    sge::cg::program::source const &_source)
{
  return sge::cg::program::replace_extra(
      _source,
      sge::cg::program::replace_extra_callback(std::bind(
          &sge::d3d9::cg::program::replace_index,
          dynamic_cast<sge::d3d9::vertex_declaration const &>(_vertex_declaration)
              .texture_coordinates(),
          std::placeholders::_1)));
}
