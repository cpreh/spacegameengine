//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/vf/client_state.hpp>
#include <sge/opengl/vf/context.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::opengl::vf::context::context(fcppt::log::object_reference const _log)
    : sge::opengl::context::base(), state_(_log)
{
}

sge::opengl::vf::context::~context() = default;

sge::opengl::vf::client_state const &sge::opengl::vf::context::state() const { return state_; }

void sge::opengl::vf::context::state(sge::opengl::vf::client_state const &_state)
{
  state_ = _state;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const sge::opengl::vf::context::static_id(sge::opengl::context::make_id());

FCPPT_PP_POP_WARNING
