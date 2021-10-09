//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_STATE_CORE_SAMPLER_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_SAMPLER_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/state/core/sampler/object_fwd.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref_map.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>

namespace sge::opengl::state::core::sampler
{

class context : public sge::opengl::context::base
{
  FCPPT_NONMOVABLE(context

  );

public:
  using parameter = sge::opengl::context::object_ref;

  explicit context(parameter);

  ~context() override;

  void set(sge::renderer::state::core::sampler::const_optional_object_ref_map const &);

  [[nodiscard]] sge::opengl::state::core::sampler::object const &
      get(sge::renderer::texture::stage) const;

  void reset();

  static sge::opengl::context::id const static_id;

private:
  using object_unique_ptr = fcppt::unique_ptr<sge::opengl::state::core::sampler::object>;

  using optional_object_ref =
      fcppt::optional::reference<sge::opengl::state::core::sampler::object const>;

  using optional_object_ref_map = std::map<sge::renderer::texture::stage, optional_object_ref>;

  object_unique_ptr const defaults_;

  optional_object_ref_map objects_;
};

}

#endif
