/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_VERTEX_BUFFER_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_BUFFER_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/renderer/vertex_buffer_types.hpp>
#include <sge/renderer/vf/dynamic/part_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief A buffer for storing parts of vertices
 *
 * A vertex buffer can hold a fixed amount of vertex parts described by a part
 * of a vertex format. After a vertex buffer has been created, it is immutable,
 * which means that its size cannot be changed.  To store data in it, it has to
 * be locked first, which will return a view for accessing the data. Unlocking
 * the buffer will make the update actually take place. In order to render any
 * geometry, vertex buffers for every part of a vertex format must be
 * activated.
 *
 * \see renderer::const_scoped_vertex_lock
 * \see renderer::scoped_vertex_lock
 * \see renderer::vertex_declaration
 * \see renderer::device::activate_vertex_buffer
 * \see renderer::device::craete_vertex_buffer
 * \see renderer::device::deactivate_vertex_buffer
 * \see renderer::vf::part
*/
class SGE_CLASS_SYMBOL vertex_buffer
{
	FCPPT_NONCOPYABLE(
		vertex_buffer
	);
protected:
	SGE_RENDERER_SYMBOL
	vertex_buffer();
public:
	/**
	 * \copydoc renderer::vertex_buffer_types::first_type
	*/
	typedef renderer::vertex_buffer_types::first_type first_type;

	/**
	 * \copydoc renderer::vertex_buffer_types::count_type
	*/
	typedef renderer::vertex_buffer_types::count_type count_type;

	/**
	 * \copydoc renderer::vertex_buffer_types::view_type
	*/
	typedef renderer::vertex_buffer_types::view_type view_type;

	/**
	 * \copydoc renderer::vertex_buffer_types::const_view_type
	*/
	typedef renderer::vertex_buffer_types::const_view_type const_view_type;

	/**
	 * \brief The size type used count bytes of the buffer
	*/
	typedef renderer::size_type size_type;

	/**
	 * \brief Specifies the end of the buffer
	*/
	SGE_RENDERER_SYMBOL
	static
	count_type const npos;

	/**
	 * \brief Locks the buffer for writing
	 *
	 * Locks the buffer using lock method \a method. The buffer will
	 * be locked starting from \a first to \a first + \a count, or
	 * the entire buffer will be locked if \a first is 0 and \a count
	 * is vertex_buffer::npos, which is the default.
	 *
	 * \param method The lock method to use, either writeonly or readwrite
	 *
	 * \param first The offset to lock the buffer from
	 *
	 * \param count The number of elements to lock, or npos for all
	 * elements
	 *
	 * \return A view that can be used to access the data
	 *
	 * \warning The behaviour is undefined if the buffer is already locked
	 * or if the region is out of range
	 *
	 * \warning The behaviour is undefined if \a method is readwrite
	 * and the buffer hasn't been created with resource_flags::readable
	*/
	virtual view_type const
	lock(
		lock_mode::type method,
		first_type first =
			first_type(0),
		count_type count
			= npos
	) = 0;

	/**
	 * \brief Locks the buffer for reading
	 *
	 * Locks the buffer starting from \a first to \a first + \a count, or
	 * the entire buffer if \a first is 0 and \a count is
	 * vertex_buffer::npos, which is the default.
	 *
	 * \param first The offset to lock the buffer from
	 *
	 * \param count The number of elements to lock, or npos for all
	 * elements
	 *
	 * \return A view that can be used to access the data
	 *
	 * \warning The behaviour is undefined if the buffer is already locked
	 * or if the region is out of range
	 *
	 * \warning The behaviour is undefined if \a method is readwrite
	 * and the buffer hasn't been created with resource_flags::readable
	*/
	virtual const_view_type const
	lock(
		first_type first
			= first_type(0),
		count_type count
			= npos
	) const = 0;

	/**
	 * \brief Unlocks the buffer
	 *
	 * Unlocking the buffer will update the modified content.
	 *
	 * \warning The behaviour is undefined if the buffer has not been locked
	*/
	virtual void
	unlock() const = 0;

	/**
	 * \brief Returns the number of vertex parts the buffer can hold
	*/
	virtual count_type const
	size() const = 0;

	/**
	 * \brief Returns the resource flags the buffer has been created with
	*/
	virtual renderer::resource_flags_field const
	resource_flags() const = 0;

	/**
	 * \brief Returns a dynamic representation of the vertex parts the
	 * buffer holds
	*/
	virtual renderer::vf::dynamic::part const
	format_part() const = 0;

	/**
	 * \brief Returns the index of the vertex format part the buffer
	 * represents
	*/
	virtual renderer::vf::dynamic::part_index const
	format_part_index() const = 0;

	SGE_RENDERER_SYMBOL
	virtual ~vertex_buffer() = 0;
};

}
}

#endif
