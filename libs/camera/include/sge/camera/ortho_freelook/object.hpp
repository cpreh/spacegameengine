//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CAMERA_ORTHO_FREELOOK_OBJECT_HPP_INCLUDED
#define SGE_CAMERA_ORTHO_FREELOOK_OBJECT_HPP_INCLUDED

#include <sge/camera/base.hpp>
#include <sge/camera/is_dynamic.hpp>
#include <sge/camera/optional_projection_matrix_fwd.hpp>
#include <sge/camera/update_duration.hpp>
#include <sge/camera/coordinate_system/object_fwd.hpp>
#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/ortho_freelook/optional_projection_rectangle.hpp>
#include <sge/camera/ortho_freelook/pan_speed.hpp>
#include <sge/camera/ortho_freelook/parameters_fwd.hpp>
#include <sge/camera/ortho_freelook/zoom_speed.hpp>
#include <sge/camera/ortho_freelook/action/mapping.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/event_base_fwd.hpp>
#include <sge/input/keyboard/event/key_fwd.hpp>
#include <sge/input/mouse/event/axis_fwd.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/rect.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::camera::ortho_freelook
{

/**
Note to self: The zoom speed measures how much of the original "viewable
rectangle" is visible after a second of zooming. A zoom speed of 0.1 means 90%
of the screen is visible after a second of zooming.

The panning speed is the amount of panning (measured in percent of the current
rectangle) that is done when the mouse moves by "one".
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL object // NOLINT(fuchsia-multiple-inheritance)
    : public virtual sge::camera::base,
      public sge::camera::is_dynamic
{
  FCPPT_NONMOVABLE(object);

public:
  SGE_CAMERA_DETAIL_SYMBOL
  explicit object(sge::camera::ortho_freelook::parameters const &);

  SGE_CAMERA_DETAIL_SYMBOL
  void zoom_speed(sge::camera::ortho_freelook::zoom_speed const &);

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL sge::camera::coordinate_system::object
  coordinate_system() const override;

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL sge::camera::optional_projection_matrix
  projection_matrix() const override;

  SGE_CAMERA_DETAIL_SYMBOL
  void process_event(sge::input::event_base const &) override;

  SGE_CAMERA_DETAIL_SYMBOL
  void update(sge::camera::update_duration) override;

  SGE_CAMERA_DETAIL_SYMBOL
  void projection_rectangle(sge::renderer::projection::rect const &);

  SGE_CAMERA_DETAIL_SYMBOL
  ~object() override;

private:
  sge::camera::ortho_freelook::action::mapping action_mapping_;

  sge::camera::ortho_freelook::optional_projection_rectangle current_projection_rectangle_;

  sge::camera::ortho_freelook::zoom_speed zoom_speed_;

  sge::camera::ortho_freelook::pan_speed pan_speed_;

  sge::renderer::projection::near near_;

  sge::renderer::projection::far far_;

  bool zoom_in_pressed_;

  bool zoom_out_pressed_;

  bool pan_pressed_;

  void mouse_axis_event(sge::input::mouse::event::axis const &);

  void key_event(sge::input::keyboard::event::key const &);
};

}

#endif
