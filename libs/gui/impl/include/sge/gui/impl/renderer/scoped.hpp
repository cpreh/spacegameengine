//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GUI_IMPL_RENDERER_SCOPED_HPP_INCLUDED
#define SGE_GUI_IMPL_RENDERER_SCOPED_HPP_INCLUDED

#include <sge/gui/impl/renderer/stateless.hpp>
#include <sge/renderer/context/ffp_ref.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object_decl.hpp>
#include <sge/sprite/state/scoped_decl.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::gui::impl::renderer
{

class scoped : public sge::gui::impl::renderer::stateless
{
  FCPPT_NONMOVABLE(scoped);

public:
  scoped(sge::renderer::device::ffp_ref, sge::renderer::context::ffp_ref);

  ~scoped() override;

private:
  using sprite_state_choices = sge::sprite::state::all_choices;

  using sprite_state = sge::sprite::state::object<sprite_state_choices>;

  using sprite_scoped_state = sge::sprite::state::scoped<sprite_state_choices>;

  sprite_state state_;

  sprite_scoped_state const scoped_state_;
};

}

#endif
