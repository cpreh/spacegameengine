//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CAMERA_BASE_HPP_INCLUDED
#define SGE_CAMERA_BASE_HPP_INCLUDED

#include <sge/camera/optional_projection_matrix_fwd.hpp>
#include <sge/camera/coordinate_system/object_fwd.hpp>
#include <sge/camera/detail/symbol.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/event_base_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::camera
{

class SGE_CORE_DETAIL_CLASS_SYMBOL base
{
  FCPPT_NONMOVABLE(base);

protected:
  base();

public:
  [[nodiscard]] virtual sge::camera::coordinate_system::object coordinate_system() const = 0;

  [[nodiscard]] virtual sge::camera::optional_projection_matrix projection_matrix() const = 0;

  virtual void process_event(sge::input::event_base const &) = 0;

  SGE_CAMERA_DETAIL_SYMBOL
  virtual ~base();
};

}

#endif
