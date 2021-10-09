//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_STATE_SCOPED_IMPL_HPP_INCLUDED
#define SGE_SPRITE_STATE_SCOPED_IMPL_HPP_INCLUDED

#include <sge/sprite/state/scoped_decl.hpp>
#include <sge/sprite/state/set.hpp>
#include <sge/sprite/state/unset.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

template <typename StateChoices>
sge::sprite::state::scoped<StateChoices>::scoped(
    render_device &_render_device,
    fcppt::reference<render_context> const _render_context,
    state_options _options,
    state_object &_object)
    : render_context_(_render_context), options_(std::move(_options))
{
  sge::sprite::state::set(_render_device, render_context_.get(), options_, _object);
}

namespace sge::sprite::state
{
template <typename StateChoices>
scoped<StateChoices>::~scoped()
{
  sge::sprite::state::unset(render_context_.get(), options_);
}
}

#endif
