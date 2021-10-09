//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_VF_CLIENT_STATE_HPP_INCLUDED
#define SGE_OPENGL_VF_CLIENT_STATE_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <set>
#include <fcppt/config/external_end.hpp>

namespace sge::opengl::vf
{

class client_state
{
public:
  using normal_state_set = std::set<GLenum>;

  using texture_state_set = std::set<sge::renderer::texture::stage>;

  using index_state_set = std::set<GLuint>;

  explicit client_state(fcppt::log::object_reference);

  void enable(GLenum);

  void disable(GLenum);

  void enable_texture(sge::renderer::texture::stage);

  void disable_texture(sge::renderer::texture::stage);

  void enable_attribute(GLuint);

  void disable_attribute(GLuint);

  [[nodiscard]] normal_state_set const &normal_states() const;

  [[nodiscard]] texture_state_set const &texture_states() const;

  [[nodiscard]] index_state_set const &attribute_states() const;

private:
  fcppt::log::object_reference log_;

  normal_state_set normal_states_;

  texture_state_set texture_states_;

  index_state_set attribute_states_;
};

}

#endif
