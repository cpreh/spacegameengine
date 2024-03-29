//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_TEXTURE_MANAGER_REF_HPP_INCLUDED
#define SGE_SCENIC_TEXTURE_MANAGER_REF_HPP_INCLUDED

#include <sge/scenic/texture_manager_fwd.hpp>
#include <fcppt/reference_impl.hpp>

namespace sge::scenic
{

using texture_manager_ref = fcppt::reference<sge::scenic::texture_manager>;

}

#endif
