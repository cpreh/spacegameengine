//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/context/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/occlusion_query/context.hpp>
#include <sge/opengl/occlusion_query/create.hpp>
#include <sge/opengl/occlusion_query/object.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/occlusion_query/object.hpp>
#include <sge/renderer/occlusion_query/object_unique_ptr.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/optional/to_exception.hpp>

sge::renderer::occlusion_query::object_unique_ptr
sge::opengl::occlusion_query::create(sge::opengl::context::object_ref const _context)
{
  return fcppt::unique_ptr_to_base<sge::renderer::occlusion_query::object>(
      fcppt::make_unique_ptr<sge::opengl::occlusion_query::object>(
          fcppt::make_cref(fcppt::optional::to_exception(
              sge::opengl::context::use<sge::opengl::occlusion_query::context>(
                  _context, _context.get().info())
                  .config(),
              []
              {
                return sge::renderer::unsupported(
                    FCPPT_TEXT("occlusion queries"), FCPPT_TEXT("1.5"), FCPPT_TEXT(""));
              }))));
}
