/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_INDEX_BUFFER_HPP_INCLUDED
#define SGE_RENDERER_INDEX_BUFFER_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/renderer/lock_mode_fwd.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/index/buffer_fwd.hpp>
#include <sge/renderer/index/buffer_types.hpp>
#include <sge/renderer/index/dynamic/format_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace index
{

/**
\brief A buffer for storing indices

An index buffer can hold a fixed amount of indices described by an index
format. Currently, there are only two index formats:

<ul>
<li>16 bit indices</li>
<li>32 bit indices</li>
</ul>

After an index buffer has been created, it is immutable, which means that
its size cannot be changed. To store data in it, it has to be locked first,
which will return a view for accessing the data. Unlocking the buffer will
make the update actually take place.
If you want to render indexed geometry, an index buffer must be used.

\see sge::renderer::device::create_index_buffer
\see sge::renderer::device::render_indexed
\see sge::renderer::index::const_scoped_lock
\see sge::renderer::index::scoped_lock
*/
class SGE_CLASS_SYMBOL buffer
{
	FCPPT_NONCOPYABLE(
		buffer
	);
protected:
	SGE_RENDERER_SYMBOL
	buffer();
public:
	/**
	\copydoc sge::renderer::index::buffer_types::first_type
	*/
	typedef sge::renderer::index::buffer_types::first_type first_type;

	/**
	\copydoc sge::renderer::index::buffer_types::count_type
	*/
	typedef sge::renderer::index::buffer_types::count_type count_type;

	/**
	\copydoc sge::renderer::index::buffer_types::view_type
	*/
	typedef sge::renderer::index::buffer_types::view_type view_type;

	/**
	\copydoc renderer::index::buffer_types::const_view_type
	*/
	typedef sge::renderer::index::buffer_types::const_view_type const_view_type;

	/**
	\brief The size type used count bytes of the buffer
	*/
	typedef sge::renderer::size_type size_type;

	/**
	\brief Specifies the end of the buffer
	*/
	SGE_RENDERER_SYMBOL
	static
	count_type const npos;

	/**
	\brief Locks the buffer for writing

	Locks the buffer using lock method \a method. The buffer will be locked
	starting from \a first to \a first + \a count, or the entire buffer
	will be locked if \a first is 0 and \a count is
	sge::renderer::index::buffer::npos, which is the default.

	\param method The lock method to use, either writeonly or readwrite

	\param first The offset to lock the buffer from

	\param count The number of elements to lock, or npos for all elements

	\return A view that can be used to access the data

	\warning The behaviour is undefined if the buffer is already locked or
	if the region is out of range

	\warning The behaviour is undefined if \a method is readwrite and the
	buffer hasn't been created with resource_flags::readable
	*/
	virtual
	view_type const
	lock(
		sge::renderer::lock_mode method,
		first_type first =
			first_type(0u),
		count_type count
			= npos
	) = 0;

	/**
	\brief Locks the buffer for reading

	Locks the buffer starting from \a first to \a first + \a count, or the
	entire buffer if \a first is 0 and \a count is sge::renderer::
	index::buffer::npos, which is the default.

	\param first The offset to lock the buffer from

	\param count The number of elements to lock, or npos for all elements

	\return A view that can be used to access the data

	\warning The behaviour is undefined if the buffer is already locked
	or if the region is out of range

	\warning The behaviour is undefined if \a method is readwrite
	and the buffer hasn't been created with resource_flags::readable
	*/
	virtual
	const_view_type const
	lock(
		first_type first
			= first_type(0u),
		count_type count
			= npos
	) const = 0;

	/**
	\brief Unlocks the buffer

	Unlocking the buffer will update the modified content.

	\warning The behaviour is undefined if the buffer has not been locked
	*/
	virtual
	void
	unlock() const = 0;

	/**
	\brief Returns the number of indices the buffer can hold
	*/
	virtual
	count_type const
	size() const = 0;

	/**
	\brief Returns the resource flags the buffer has been created with
	*/
	virtual
	sge::renderer::resource_flags_field const
	resource_flags() const = 0;

	/**
	\brief Returns the format the buffer uses
	*/
	virtual
	sge::renderer::index::dynamic::format
	format() const = 0;

	SGE_RENDERER_SYMBOL
	virtual
	~buffer() = 0;
};

}
}
}

#endif
