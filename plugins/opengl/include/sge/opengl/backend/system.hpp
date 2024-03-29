//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_BACKEND_SYSTEM_HPP_INCLUDED
#define SGE_OPENGL_BACKEND_SYSTEM_HPP_INCLUDED

#include <sge/opengl/backend/context_unique_ptr.hpp>
#include <sge/opengl/backend/system_fwd.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::opengl::backend
{

class system
{
  FCPPT_NONMOVABLE(system);

protected:
  system();

public:
  virtual ~system();

  [[nodiscard]] virtual awl::visual::object_unique_ptr
  create_visual(sge::renderer::pixel_format::object const &) = 0;

  [[nodiscard]] virtual sge::opengl::backend::context_unique_ptr
      create_context(sge::window::object_ref) = 0;
};

}

#endif
