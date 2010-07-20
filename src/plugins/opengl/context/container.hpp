/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_OPENGL_CONTEXT_CONTAINER_HPP_INCLUDED
#define SGE_OPENGL_CONTEXT_CONTAINER_HPP_INCLUDED

#include "base_fwd.hpp"
#include <fcppt/noncopyable.hpp>
#include <fcppt/auto_ptr.hpp>
#include <vector>
#include <cstddef>

namespace sge
{
namespace opengl
{
namespace context
{

/// Simple container that can hold null values
/**
 * This is a simple replacement for boost::ptr_vector.
 * It has the ability to hold null pointers,
 * but will still delete them on its own.
 * Special care has to be taken because various operations can throw.
*/
class container
{
	FCPPT_NONCOPYABLE(container)
public:
	typedef base value_type;

	typedef value_type *pointer;

	typedef std::auto_ptr<
		value_type
	> auto_ptr;

	typedef std::size_t size_type;

	container();

	~container();

	/// Returns the element or null if it is not in the container
	/**
	 * Returning 0 can mean that the element has been either initialized to zero,
	 * or that it is not present because the container is not big enough.
	*/
	pointer
	get(
		size_type
	) const;

	/// Inserts a new element at @a index.
	/**
	 * Returns true if the element was not present.
	*/
	bool
	insert(
		size_type index,
		auto_ptr
	);
private:
	void
	destroy();

	typedef std::vector<
		pointer
	> inner_container;

	inner_container elements_;
};

}
}
}

#endif
