/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_BASIC_SCOPED_BUFFER_LOCK_HPP_INCLUDED
#define SGE_RENDERER_BASIC_SCOPED_BUFFER_LOCK_HPP_INCLUDED

#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/npos.hpp>
#include <sge/renderer/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief A buffer lock that is not readonly.
 *
 * Used for locking renderer::vertex_buffer and renderer::index_buffer. It
 * locks the buffer in the constructor and unlocks it in the destructor.
 *
 * \see sge::renderer::scoped_vertex_lock
 * \see sge::renderer::scoped_index_lock
*/
template<
	typename Buffer,
	typename Types
>
class basic_scoped_buffer_lock
{
	FCPPT_NONCOPYABLE(
		basic_scoped_buffer_lock
	);
public:
	/**
	 * \brief The offset type
	 *
	 * Used to tell at which element the lock will start.
	*/
	typedef typename Types::first_type first_type;

	/**
	 * \brief The count type
	 *
	 * Used to tell how many elements will be locked.
	*/
	typedef typename Types::count_type count_type;

	/**
	 * \brief The view type of the lock.
	*/
	typedef typename Types::view_type view_type;

	/**
	 * \brief Locks a buffer
	 *
	 * Locks \a buffer, using the lock method \a method. The buffer will
	 * be locked starting from \a first to \a first + \a count, or the
	 * entire will be locked if \a first is 0 and \a count is
	 * renderer::npos, which is the default.
	 *
	 * \param buffer The buffer to lock
	 *
	 * \param method The lock method to use, either writeonly or readwrite
	 *
	 * \param first The offset to lock the buffer from
	 *
	 * \param count The number of elements to lock, or npos for all
	 * elements
	 *
	 * \warning The behaviour is undefined if the buffer is already locked
	 * or if the region is out of range
	*/
	SGE_RENDERER_SYMBOL
	basic_scoped_buffer_lock(
		Buffer &buffer,
		renderer::lock_mode::type method,
		first_type first =
			first_type(0),
		count_type count =
			count_type(
				renderer::npos()
			)
	);

	/**
	 * \brief Obtain the view of the locked region
	 *
	 * \return The view of the locked region
	*/
	SGE_RENDERER_SYMBOL
	view_type const
	value() const;

	/**
	 * \brief Unlocks the buffer
	 *
	 * \warning The behaviour is undefined if the buffer has been locked
	 * again or unlocked in between the constructor and destructor
	*/
	SGE_RENDERER_SYMBOL
	~basic_scoped_buffer_lock();
private:
	Buffer &buffer_;

	view_type const view_;
};

}
}

#endif
