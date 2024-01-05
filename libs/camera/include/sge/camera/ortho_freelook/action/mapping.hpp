//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CAMERA_ORTHO_FREELOOK_ACTION_MAPPING_HPP_INCLUDED
#define SGE_CAMERA_ORTHO_FREELOOK_ACTION_MAPPING_HPP_INCLUDED

#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/ortho_freelook/action/activate_pan.hpp>
#include <sge/camera/ortho_freelook/action/mapping_fwd.hpp> // IWYU pragma: keep
#include <sge/camera/ortho_freelook/action/zoom_in.hpp>
#include <sge/camera/ortho_freelook/action/zoom_out.hpp>

namespace sge::camera::ortho_freelook::action
{

/**
\brief A mapping from camera "actions" to key codes
\ingroup sgecamera
*/
class mapping
{
public:
  SGE_CAMERA_DETAIL_SYMBOL
  mapping(
      sge::camera::ortho_freelook::action::zoom_in const &,
      sge::camera::ortho_freelook::action::zoom_out const &,
      sge::camera::ortho_freelook::action::activate_pan const &);

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL sge::camera::ortho_freelook::action::zoom_in const &
  zoom_in() const;

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL sge::camera::ortho_freelook::action::zoom_out const &
  zoom_out() const;

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL sge::camera::ortho_freelook::action::activate_pan const &
  activate_pan() const;

private:
  sge::camera::ortho_freelook::action::zoom_in zoom_in_;
  sge::camera::ortho_freelook::action::zoom_out zoom_out_;
  sge::camera::ortho_freelook::action::activate_pan activate_pan_;
};

}

#endif
