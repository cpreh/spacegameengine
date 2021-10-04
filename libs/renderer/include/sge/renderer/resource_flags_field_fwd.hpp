//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_RESOURCE_FLAGS_FIELD_FWD_HPP_INCLUDED
#define SGE_RENDERER_RESOURCE_FLAGS_FIELD_FWD_HPP_INCLUDED

#include <sge/renderer/resource_flags.hpp>
#include <fcppt/container/bitfield/object_fwd.hpp>


namespace sge::renderer
{

/**
\brief A bitfield that can hold flags from sge::renderer::resource_flags

\ingroup sge_renderer
*/
using
resource_flags_field
=
fcppt::container::bitfield::object<
	sge::renderer::resource_flags
>;

}

#endif
