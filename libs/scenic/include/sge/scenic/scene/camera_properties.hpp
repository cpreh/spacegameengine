//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_SCENE_CAMERA_PROPERTIES_HPP_INCLUDED
#define SGE_SCENIC_SCENE_CAMERA_PROPERTIES_HPP_INCLUDED

#include <sge/camera/coordinate_system/object.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/fov.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/scenic/detail/symbol.hpp>

namespace sge::scenic::scene
{
class camera_properties
{
public:
  SGE_SCENIC_DETAIL_SYMBOL
  camera_properties(
      sge::camera::coordinate_system::object,
      sge::renderer::projection::fov const &,
      sge::renderer::projection::near const &,
      sge::renderer::projection::far const &);

  [[nodiscard]] SGE_SCENIC_DETAIL_SYMBOL sge::camera::coordinate_system::object const &
  coordinate_system() const;

  [[nodiscard]] SGE_SCENIC_DETAIL_SYMBOL sge::renderer::projection::fov const &fov() const;

  [[nodiscard]] SGE_SCENIC_DETAIL_SYMBOL sge::renderer::projection::near const &near() const;

  [[nodiscard]] SGE_SCENIC_DETAIL_SYMBOL sge::renderer::projection::far const &far() const;

private:
  sge::camera::coordinate_system::object coordinate_system_;

  sge::renderer::projection::fov fov_;

  sge::renderer::projection::near near_;

  sge::renderer::projection::far far_;
};

}

#endif
