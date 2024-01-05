//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CAMERA_ORTHO_FREELOOK_PROJECTION_RECTANGLE_FROM_VIEWPORT_HPP_INCLUDED
#define SGE_CAMERA_ORTHO_FREELOOK_PROJECTION_RECTANGLE_FROM_VIEWPORT_HPP_INCLUDED

#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/ortho_freelook/object_fwd.hpp>
#include <sge/camera/ortho_freelook/projection_rectangle_from_viewport_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/target/viewport_fwd.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/signal/auto_connection.hpp>

namespace sge::camera::ortho_freelook
{

class projection_rectangle_from_viewport
{
  FCPPT_NONMOVABLE(projection_rectangle_from_viewport);

public:
  SGE_CAMERA_DETAIL_SYMBOL
  projection_rectangle_from_viewport(
      fcppt::reference<sge::camera::ortho_freelook::object>, sge::viewport::manager_ref);

  SGE_CAMERA_DETAIL_SYMBOL
  ~projection_rectangle_from_viewport();

private:
  fcppt::reference<sge::camera::ortho_freelook::object> const camera_;

  fcppt::signal::auto_connection const viewport_callback_connection_;

  void viewport_callback(sge::renderer::target::viewport const &);
};

}

#endif
