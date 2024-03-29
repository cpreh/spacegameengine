//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_VF_TEXCOORD_HPP_INCLUDED
#define SGE_SCENIC_VF_TEXCOORD_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vf/index.hpp>
#include <sge/renderer/vf/texpos.hpp>

namespace sge::scenic::vf
{

using texcoord = sge::renderer::vf::texpos<sge::renderer::scalar, 2, sge::renderer::vf::index<0U>>;

}

#endif
