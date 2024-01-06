//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_RENDER_CONTEXT_CG_LIGHT_DIRECTIONAL_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_CG_LIGHT_DIRECTIONAL_HPP_INCLUDED

#include <sge/cg/program/object_ref.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/scenic/render_context/ambient_color.hpp>
#include <sge/scenic/render_context/diffuse_color.hpp>
#include <sge/scenic/render_context/specular_color.hpp>
#include <sge/scenic/render_context/cg/light/index.hpp>
#include <sge/scenic/render_context/light/direction_fwd.hpp>
#include <sge/shader/parameter/vector.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::scenic::render_context::cg::light
{

class directional
{
  FCPPT_NONMOVABLE(directional);

public:
  directional(sge::cg::program::object_ref, sge::scenic::render_context::cg::light::index const &);

  void diffuse_color(sge::scenic::render_context::diffuse_color const &);

  void specular_color(sge::scenic::render_context::specular_color const &);

  void ambient_color(sge::scenic::render_context::ambient_color const &);

  void camera_space_direction(sge::scenic::render_context::light::direction const &);

  ~directional();

private:
  sge::shader::parameter::vector<sge::renderer::scalar, 4> diffuse_color_;
  sge::shader::parameter::vector<sge::renderer::scalar, 4> specular_color_;
  sge::shader::parameter::vector<sge::renderer::scalar, 4> ambient_color_;
  sge::shader::parameter::vector<sge::renderer::scalar, 3> camera_space_direction_;
};

}

#endif
