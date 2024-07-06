//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_GLX_VISUAL_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_GLX_VISUAL_OBJECT_HPP_INCLUDED

#include <sge/renderer/visual_base.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/x11/visual/info_unique_ptr.hpp>
#include <awl/backends/x11/visual/wrapped.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::opengl::glx::visual
{

class object // NOLINT(fuchsia-multiple-inheritance)
    : public awl::backends::x11::visual::wrapped,
      public sge::renderer::visual_base
{
  FCPPT_NONMOVABLE(object);

public:
  object(
      awl::backends::x11::visual::info_unique_ptr &&, sge::renderer::pixel_format::object const &);

  ~object() override;
};

}

#endif
