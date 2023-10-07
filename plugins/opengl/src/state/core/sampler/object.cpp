//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/state/unary_object_impl.hpp>
#include <sge/opengl/state/core/sampler/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/renderer/state/core/sampler/object.hpp>

template class sge::opengl::state::
    unary_object<sge::renderer::state::core::sampler::object, sge::opengl::texture::binding>;
