//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/state/unary_object_impl.hpp>
#include <sge/opengl/state/ffp/transform/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>

template class sge::opengl::state::unary_object<
    sge::renderer::state::ffp::transform::object,
    sge::renderer::state::ffp::transform::mode>;
