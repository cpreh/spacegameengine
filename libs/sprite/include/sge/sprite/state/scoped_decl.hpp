//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_STATE_SCOPED_DECL_HPP_INCLUDED
#define SGE_SPRITE_STATE_SCOPED_DECL_HPP_INCLUDED

#include <sge/sprite/state/object_fwd.hpp>
#include <sge/sprite/state/options_decl.hpp>
#include <sge/sprite/state/render_context.hpp>
#include <sge/sprite/state/render_device.hpp>
#include <sge/sprite/state/scoped_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>

namespace sge::sprite::state
{

template <typename StateChoices>
class scoped
{
  FCPPT_NONMOVABLE(scoped);

public:
  using render_device = sge::sprite::state::render_device<StateChoices>;

  using render_context = sge::sprite::state::render_context<StateChoices>;

  using state_options = sge::sprite::state::options<StateChoices>;

  using state_object = sge::sprite::state::object<StateChoices>;

  scoped(render_device &, fcppt::reference<render_context>, state_options, state_object &);

  ~scoped();

private:
  fcppt::reference<render_context> const render_context_;

  state_options const options_;
};

}

#endif
