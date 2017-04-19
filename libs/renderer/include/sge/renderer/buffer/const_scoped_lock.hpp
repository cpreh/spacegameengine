/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_BUFFER_CONST_SCOPED_LOCK_HPP_INCLUDED
#define SGE_RENDERER_BUFFER_CONST_SCOPED_LOCK_HPP_INCLUDED

#include <sge/image/box_fwd.hpp>
#include <sge/renderer/buffer/const_scoped_lock_fwd.hpp>
#include <sge/renderer/buffer/readable_fwd.hpp>
#include <sge/renderer/buffer/traits/const_view.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace buffer
{

/**
\brief Locks a buffer readonly.

\ingroup sge_renderer

Creates a box with value type sge::renderer::size_type.
Used for locking of buffers readonly. It locks the buffer in the constructor
and unlocks it in the destructor.
*/
template<
	typename Tag
>
class const_scoped_lock
{
	FCPPT_NONCOPYABLE(
		const_scoped_lock
	);
public:
	typedef
	sge::renderer::buffer::readable<
		Tag
	>
	buffer_type;

	typedef
	sge::image::box<
		Tag
	>
	lock_area;

	typedef
	sge::renderer::buffer::traits::const_view<
		Tag
	>
	const_view;

	/**
	\brief Locks an entire buffer

	\param buffer The buffer to lock

	\warning The behavior is undefined if the buffer is already locked
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	explicit
	const_scoped_lock(
		buffer_type const &buffer
	);

	/**
	\brief Locks a portion of a buffer

	Locks the portion of \a buffer described by \a area

	\param buffer The buffer to lock

	\param area The area to lock

	\warning The behavior is undefined if the buffer is already locked

	\warning The behavior is undefined if \a area is out of range
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	const_scoped_lock(
		buffer_type const &buffer,
		lock_area const &area
	);

	/**
	\brief Obtain the view of the locked region

	\return The view of the locked region
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	const_view
	value() const;

	/**
	\brief Unlocks the buffer

	\warning The behavior is undefined if the buffer has been
	locked again or unlocked in between the constructor and destructor
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	~const_scoped_lock();
private:
	buffer_type const &buffer_;

	const_view const view_;
};

}
}
}

#endif
