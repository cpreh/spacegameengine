/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_COLOR_BUFFER_CONST_BASIC_SCOPED_LOCK_HPP_INCLUDED
#define SGE_RENDERER_COLOR_BUFFER_CONST_BASIC_SCOPED_LOCK_HPP_INCLUDED

#include <sge/image/view/const_object.hpp>
#include <sge/renderer/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace color_buffer
{

/**
\brief Locks a color buffer readonly.

Used for locking of color buffers readonly. It locks the color buffer in the
constructor and unlocks it in the destructor.
*/
template<
	typename Buffer
>
class const_basic_scoped_lock
{
	FCPPT_NONCOPYABLE(
		const_basic_scoped_lock
	);
public:
	typedef Buffer buffer_type;

	typedef typename buffer_type::lock_area lock_area;

	typedef typename buffer_type::const_view const_view;

	/**
	\brief Locks an entire color buffer

	\param buffer The buffer to lock

	\warning The behavior is undefined if the color buffer is already
	locked
	*/
	SGE_RENDERER_SYMBOL
	explicit
	const_basic_scoped_lock(
		buffer_type const &buffer
	);

	/**
	\brief Locks a portion of a color buffer

	Locks the portion of \a buffer described by \a area

	\param buffer The color buffer to lock

	\param area The area to lock

	\warning The behavior is undefined if the color buffer is already
	locked

	\warning The behavior is undefined if \a area is out of range
	*/
	SGE_RENDERER_SYMBOL
	const_basic_scoped_lock(
		buffer_type const &buffer,
		lock_area const &area
	);

	/**
	\brief Obtain the view of the locked region

	\return The view of the locked region
	*/
	SGE_RENDERER_SYMBOL
	const_view const
	value() const;

	/**
	\brief Unlocks the color buffer

	\warning The behavior is undefined if the color buffer has been
	locked again or unlocked in between the constructor and destructor
	*/
	SGE_RENDERER_SYMBOL
	~const_basic_scoped_lock();
private:
	buffer_type const &buffer_;

	const_view const view_;
};

}
}
}

#endif
