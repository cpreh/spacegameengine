//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_RENDER_CONTEXT_FOG_OPTIONAL_PROPERTIES_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_FOG_OPTIONAL_PROPERTIES_HPP_INCLUDED

#include <sge/scenic/render_context/fog/properties.hpp>
#include <fcppt/optional/object_impl.hpp>

namespace sge::scenic::render_context::fog
{

using optional_properties = fcppt::optional::object<sge::scenic::render_context::fog::properties>;

}

#endif
