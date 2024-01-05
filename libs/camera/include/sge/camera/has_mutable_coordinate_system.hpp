//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CAMERA_HAS_MUTABLE_COORDINATE_SYSTEM_HPP_INCLUDED
#define SGE_CAMERA_HAS_MUTABLE_COORDINATE_SYSTEM_HPP_INCLUDED

#include <sge/camera/base.hpp>
#include <sge/camera/has_mutable_coordinate_system_fwd.hpp>
#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/coordinate_system/object_fwd.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::camera
{

class SGE_CORE_DETAIL_CLASS_SYMBOL has_mutable_coordinate_system : public virtual sge::camera::base
{
  FCPPT_NONMOVABLE(has_mutable_coordinate_system);

protected:
  SGE_CAMERA_DETAIL_SYMBOL
  has_mutable_coordinate_system();

public:
  virtual void update_coordinate_system(sge::camera::coordinate_system::object const &) = 0;

  SGE_CAMERA_DETAIL_SYMBOL
  ~has_mutable_coordinate_system() override;
};

}

#endif
