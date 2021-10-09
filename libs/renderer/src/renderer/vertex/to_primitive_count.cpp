//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/exception.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/to_primitive_count.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>

sge::renderer::primitive_count sge::renderer::vertex::to_primitive_count(
    sge::renderer::vertex::count const _vertex_count,
    sge::renderer::primitive_type const _primitive_type)
{
  switch (_primitive_type)
  {
  case sge::renderer::primitive_type::point_list:
    return sge::renderer::primitive_count(_vertex_count.get());
  case sge::renderer::primitive_type::line_list:
    if ((_vertex_count.get() % 2U) != 0U)
    {
      throw sge::renderer::exception(
          FCPPT_TEXT("nonindexed_primitive_count(): line needs a multiple of two vertices!"));
    }

    return sge::renderer::primitive_count(_vertex_count.get() / 2U);

  case sge::renderer::primitive_type::line_strip:
    if (_vertex_count.get() <= 1U)
    {
      throw sge::renderer::exception(
          FCPPT_TEXT("nonindexed_primitive_count(): line_strip needs at least two vertices!"));
    }

    return sge::renderer::primitive_count(_vertex_count.get() - 1U);
  case sge::renderer::primitive_type::triangle_strip:
  case sge::renderer::primitive_type::triangle_fan:
    if (_vertex_count.get() <= 2U)
    {
      throw sge::renderer::exception(FCPPT_TEXT("nonindexed_primitive_count(): triangle_fan and "
                                                "triangle_strip need at least three vertices!"));
    }

    return sge::renderer::primitive_count(_vertex_count.get() - 2U);
  case sge::renderer::primitive_type::triangle_list:
    if ((_vertex_count.get() % 3U) != 0U)
    {
      throw sge::renderer::exception(
          FCPPT_TEXT("nonindexed_primitive_count(): triangle needs a multiple of three vertices!"));
    }

    return sge::renderer::primitive_count(_vertex_count.get() / 3U);
  }

  FCPPT_ASSERT_UNREACHABLE;
}
