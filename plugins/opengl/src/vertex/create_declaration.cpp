//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/vertex/create_declaration.hpp>
#include <sge/opengl/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters_fwd.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/object_reference.hpp>

sge::renderer::vertex::declaration_unique_ptr sge::opengl::vertex::create_declaration(
    fcppt::log::object_reference const _log,
    sge::opengl::context::object_ref const _context,
    sge::renderer::vertex::declaration_parameters const &_parameters)
{
  return fcppt::unique_ptr_to_base<sge::renderer::vertex::declaration>(
      fcppt::make_unique_ptr<sge::opengl::vertex::declaration>(_log, _context, _parameters));
}
