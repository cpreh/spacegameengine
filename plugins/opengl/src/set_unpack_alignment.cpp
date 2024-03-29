//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/pixel_store_context.hpp>
#include <sge/opengl/pixel_store_int.hpp>
#include <sge/opengl/set_unpack_alignment.hpp>
#include <sge/opengl/unpack_alignment.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep

void sge::opengl::set_unpack_alignment(
    sge::opengl::context::object &_context, sge::opengl::unpack_alignment const _alignment)
{
  auto &context{
      sge::opengl::context::use<sge::opengl::pixel_store_context>(fcppt::make_ref(_context))};

  if (context.unpack_alignment() == _alignment)
  {
    return;
  }

  sge::opengl::pixel_store_int(GL_UNPACK_ALIGNMENT, _alignment.get());

  context.unpack_alignment(_alignment);
}
