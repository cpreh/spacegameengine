//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_VF_FP_ACTOR_HPP_INCLUDED
#define SGE_OPENGL_VF_FP_ACTOR_HPP_INCLUDED

#include <sge/opengl/vf/actor_parameters_fwd.hpp>
#include <sge/opengl/vf/client_state_combiner_ref.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/opengl/vf/pointer_actor.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::opengl::vf
{

class fp_actor : public sge::opengl::vf::pointer_actor
{
  FCPPT_NONMOVABLE(fp_actor);

public:
  ~fp_actor() override = 0;

protected:
  fp_actor(sge::opengl::vf::actor_parameters const &, GLenum client_state);

private:
  void
  operator()(sge::opengl::vf::client_state_combiner_ref, sge::opengl::vf::pointer) const override;

  void unuse(sge::opengl::vf::client_state_combiner_ref) const override;

  virtual void on_use(sge::opengl::vf::pointer) const = 0;

  GLenum const client_state_;
};

}

#endif
