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


#ifndef SGE_RENDERER_BASIC_BUFFER_SCOPED_LOCK_HPP_INCLUDED
#define SGE_RENDERER_BASIC_BUFFER_SCOPED_LOCK_HPP_INCLUDED

#include <sge/image/view/object.hpp>
#include <sge/renderer/basic_buffer_scoped_lock_fwd.hpp>
#include <sge/renderer/lock_mode_fwd.hpp>
#include <sge/renderer/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{

/**
\brief Locks a buffer readwrite or writeonly.

\ingroup sge_renderer

Used for locking of buffers readwrite or writeonly. It locks the buffer in the
constructor and unlocks it in the destructor.
*/
template<
	typename Buffer
>
class basic_buffer_scoped_lock
{
	FCPPT_NONCOPYABLE(
		basic_buffer_scoped_lock
	);
public:
	typedef Buffer buffer_type;

	typedef typename buffer_type::lock_area lock_area;

	typedef typename buffer_type::view view;

	/**
	\brief Locks an entire buffer

	\param buffer The buffer to lock

	\param mode The lock mode to use

	\warning The behavior is undefined if the buffer is already locked
	*/
	SGE_RENDERER_SYMBOL
	basic_buffer_scoped_lock(
		buffer_type &buffer,
		sge::renderer::lock_mode mode
	);

	/**
	\brief Locks a portion of a buffer

	Locks the portion of \a buffer described by \a area

	\param buffer The buffer to lock

	\param area The area to lock

	\param mode The lock mode to use

	\warning The behavior is undefined if the buffer is already locked

	\warning The behavior is undefined if \a area is out of range
	*/
	SGE_RENDERER_SYMBOL
	basic_buffer_scoped_lock(
		buffer_type &buffer,
		lock_area const &area,
		sge::renderer::lock_mode mode
	);

	/**
	\brief Obtain the view of the locked region

	\return The view of the locked region
	*/
	SGE_RENDERER_SYMBOL
	view const
	value() const;

	/**
	\brief Unlocks the buffer

	\warning The behavior is undefined if the buffer has been locked again
	or unlocked in between the constructor and destructor
	*/
	SGE_RENDERER_SYMBOL
	~basic_buffer_scoped_lock();
private:
	buffer_type &buffer_;

	view const view_;
};

}
}

#endif
