//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_SCENE_PROTOTYPE_HPP_INCLUDED
#define SGE_SCENIC_SCENE_PROTOTYPE_HPP_INCLUDED

#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/ambient_color.hpp>
#include <sge/scenic/render_context/fog/optional_properties.hpp>
#include <sge/scenic/render_context/fog/properties.hpp>
#include <sge/scenic/render_context/light/sequence.hpp>
#include <sge/scenic/scene/camera_properties.hpp>
#include <sge/scenic/scene/entity_sequence.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/optional/object.hpp>

namespace sge::scenic::scene
{
class prototype
{
  FCPPT_NONMOVABLE(prototype);

public:
  SGE_SCENIC_DETAIL_SYMBOL
  prototype(
      sge::scenic::scene::camera_properties,
      sge::scenic::render_context::fog::optional_properties,
      sge::scenic::render_context::ambient_color);

  [[nodiscard]] SGE_SCENIC_DETAIL_SYMBOL sge::scenic::scene::entity_sequence const &
  entities() const;

  [[nodiscard]] SGE_SCENIC_DETAIL_SYMBOL sge::scenic::scene::entity_sequence &entities();

  [[nodiscard]] SGE_SCENIC_DETAIL_SYMBOL sge::scenic::render_context::light::sequence const &
  lights() const;

  [[nodiscard]] SGE_SCENIC_DETAIL_SYMBOL sge::scenic::render_context::light::sequence &lights();

  [[nodiscard]] SGE_SCENIC_DETAIL_SYMBOL sge::scenic::scene::camera_properties const &
  camera() const;

  [[nodiscard]] SGE_SCENIC_DETAIL_SYMBOL
      sge::scenic::render_context::fog::optional_properties const &
      fog() const;

  [[nodiscard]] SGE_SCENIC_DETAIL_SYMBOL sge::scenic::render_context::ambient_color const &
  ambient_color() const;

  SGE_SCENIC_DETAIL_SYMBOL
  ~prototype();

private:
  sge::scenic::scene::camera_properties camera_;
  sge::scenic::render_context::fog::optional_properties fog_;
  sge::scenic::render_context::ambient_color ambient_color_;
  sge::scenic::scene::entity_sequence entities_;
  sge::scenic::render_context::light::sequence lights_;
};
}

#endif
