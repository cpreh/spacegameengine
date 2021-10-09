//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_STATE_CORE_SAMPLER_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_SAMPLER_OBJECT_HPP_INCLUDED

#include <sge/opengl/state/unary_object.hpp>
#include <sge/opengl/state/core/sampler/object_fwd.hpp>
#include <sge/opengl/texture/binding.hpp>
#include <sge/renderer/state/core/sampler/object.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

extern template class sge::opengl::state::
    unary_object<sge::renderer::state::core::sampler::object, sge::opengl::texture::binding>;

FCPPT_PP_POP_WARNING

#endif
