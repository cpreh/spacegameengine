//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VF_DYNAMIC_EXTRA_ANY_FWD_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_EXTRA_ANY_FWD_HPP_INCLUDED

#include <sge/renderer/vf/dynamic/color_fwd.hpp>
#include <sge/renderer/vf/dynamic/vector_fwd.hpp>
#include <fcppt/variant/object_fwd.hpp>

namespace sge::renderer::vf::dynamic
{

using extra_any =
    fcppt::variant::object<sge::renderer::vf::dynamic::vector, sge::renderer::vf::dynamic::color>;

}

#endif
