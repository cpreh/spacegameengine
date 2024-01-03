//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_LOCK_MODE_HPP_INCLUDED
#define SGE_RENDERER_LOCK_MODE_HPP_INCLUDED

#include <sge/renderer/lock_mode_fwd.hpp> // IWYU pragma: keep

namespace sge::renderer
{

/**
\brief Mode for accessing resources

\ingroup sge_renderer
*/
enum class lock_mode
{
  /**
	\brief Locks a resource for writing only

	This is always safe to use and is the most efficient way to update a
	resource.
	*/
  writeonly,
  /**
	\brief Locks a resource for reading and writing

	The contents of the resource can be read and written at the same time.
	This can only be used if the resource has been created with
	sge::renderer::resource_flags::readable. Reading a resource can slow
	locking and unlocking down a lot.
	*/
  readwrite
};

}

#endif
