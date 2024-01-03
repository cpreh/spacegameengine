//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_RESOURCE_FLAGS_HPP_INCLUDED
#define SGE_RENDERER_RESOURCE_FLAGS_HPP_INCLUDED

#include <sge/renderer/resource_flags_fwd.hpp> // IWYU pragma: keep

namespace sge::renderer
{

/**
\brief Flags used when creating resources

\ingroup sge_renderer
*/
enum class resource_flags
{
  /**
	\brief Makes the resource dynamic

	A driver shall try to make a compromise so that dynamic resources are
	faster to lock/unlock but may be also slower to render. A dynamic
	resource must be completely updated for every render block, otherwise
	its contents will be undefined. This is to ensure that sge doesn't have
	to make a copy of the internal data. Dynamic resources are most useful
	if the contents change every frame anyway, e.g. in a sprite system.
	*/
  dynamic,
  /**
	\brief Makes a resource readable

	By default, a resource is not readable which means it cannot be locked
	so that data can be read from it. A readable resource might be slower
	to render, slower to lock or unlock or might require more memory.
	*/
  readable,
  fcppt_maximum = readable
};

}

#endif
