//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_STATE_FFP_TRANSFORM_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_TRANSFORM_OBJECT_HPP_INCLUDED

#include <sge/opengl/state/unary_object.hpp>
#include <sge/opengl/state/ffp/transform/object_fwd.hpp> // IWYU pragma: export
#include <sge/renderer/state/ffp/transform/mode_fwd.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

extern template class sge::opengl::state::unary_object<
    sge::renderer::state::ffp::transform::object,
    sge::renderer::state::ffp::transform::mode>;

FCPPT_PP_POP_WARNING

#endif
