//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CAMERA_FIRST_PERSON_ACTION_MAPPING_HPP_INCLUDED
#define SGE_CAMERA_FIRST_PERSON_ACTION_MAPPING_HPP_INCLUDED

#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/first_person/action/backward.hpp>
#include <sge/camera/first_person/action/down.hpp>
#include <sge/camera/first_person/action/forward.hpp>
#include <sge/camera/first_person/action/left.hpp>
#include <sge/camera/first_person/action/right.hpp>
#include <sge/camera/first_person/action/up.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <fcppt/optional/object_impl.hpp>

namespace sge::camera::first_person::action
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
      sge::camera::first_person::action::left const &,
      sge::camera::first_person::action::right const &,
      sge::camera::first_person::action::up const &,
      sge::camera::first_person::action::down const &,
      sge::camera::first_person::action::forward const &,
      sge::camera::first_person::action::backward const &);

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL sge::camera::first_person::action::left const &
  left() const;

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL sge::camera::first_person::action::right const &
  right() const;

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL sge::camera::first_person::action::up const &up() const;

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL sge::camera::first_person::action::down const &
  down() const;

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL sge::camera::first_person::action::forward const &
  forward() const;

  [[nodiscard]] SGE_CAMERA_DETAIL_SYMBOL sge::camera::first_person::action::backward const &
  backward() const;

private:
  sge::camera::first_person::action::left left_;
  sge::camera::first_person::action::right right_;
  sge::camera::first_person::action::up up_;
  sge::camera::first_person::action::down down_;
  sge::camera::first_person::action::forward forward_;
  sge::camera::first_person::action::backward backward_;
};

}

#endif
