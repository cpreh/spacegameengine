/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_BASIC_BUFFER_HPP_INCLUDED
#define SGE_RENDERER_BASIC_BUFFER_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/image/traits/box_fwd.hpp>
#include <sge/image/traits/color_tag.hpp>
#include <sge/image/traits/const_view_fwd.hpp>
#include <sge/image/traits/dim_fwd.hpp>
#include <sge/image/traits/format_fwd.hpp>
#include <sge/image/traits/view_fwd.hpp>
#include <sge/renderer/basic_buffer_fwd.hpp>
#include <sge/renderer/lock_mode_fwd.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{

/**
\brief A lockable buffer

\ingroup sge_renderer
*/
template<
	typename ImageTag
>
class SGE_CORE_DETAIL_CLASS_SYMBOL basic_buffer
{
	FCPPT_NONCOPYABLE(
		basic_buffer
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	basic_buffer();
public:
	virtual
	~basic_buffer() = 0;

	/**
	\brief The image tag

	The image tag is used by generic algorithms that abstract 2D/3D and
	formats.
	*/
	typedef
	ImageTag
	image_tag;

	/**
	\brief The size type

	Specifies a size in pixels
	*/
	typedef
	sge::renderer::size_type
	size_type;

	/**
	\brief The dimension type

	Specifies a dimension in pixels
	*/
	typedef
	typename
	sge::image::traits::dim<
		ImageTag
	>::type
	dim;

	/**
	\brief The lock area type

	Specifies the lock area in pixels
	*/
	typedef
	typename
	sge::image::traits::box<
		ImageTag
	>::type
	lock_area;

	/**
	\brief The view type

	The view type of nonconst locks
	*/
	typedef
	typename
	sge::image::traits::view<
		ImageTag
	>::type
	view;

	/**
	\brief The const view type

	The view type of const locks
	*/
	typedef
	typename
	sge::image::traits::const_view<
		ImageTag
	>::type
	const_view;

	/**
	\brief The color tag associated with the image tag
	*/
	typedef
	typename
	sge::image::traits::color_tag<
		ImageTag
	>::type
	color_tag;

	typedef
	typename
	sge::image::traits::format<
		color_tag
	>::type
	color_format;

	/**
	\brief Locks the whole buffer readonly

	Locks the whole buffer readonly

	\return The view of the locked region

	\warning The behavior is undefined if the buffer is already locked
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	const_view const
	lock() const;

	/**
	\brief Locks a portion of the buffer readonly

	Reads the portion of the buffer specified by \a area readonly.

	\param area The area to lock

	\return The view of the locked region

	\warning The behavior is undefined if the buffer is already locked

	\warning The behavior is undefined if \a area is out of range
	*/
	virtual
	const_view const
	lock(
		lock_area const &area
	) const = 0;

	/**
	\brief Locks the whole buffer readwrite or writeonly

	Locks the whole buffer readwrite or writeonly, depending on \a mode.

	\param mode Tells if the buffer should be locked readwrite or writeonly

	\return The view of the locked region

	\warning The behavior is undefined if the buffer is already locked
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	view const
	lock(
		sge::renderer::lock_mode mode
	);

	/**
	\brief Locks a portion of the buffer readwrite or writeonly

	Locks the porition of the buffer specified by \a area readwrite or
	writeonly, depending on \a mode.

	\param area The area to lock

	\param mode Tells if the buffer should be locked readwrite or writeonly

	\return The view of the locked region

	\warning The behavior is undefined if the buffer is already locked
	*/
	virtual
	view const
	lock(
		lock_area const &area,
		sge::renderer::lock_mode mode
	) = 0;

	/**
	\brief Unlocks the buffer

	Unlocks the currently locked buffer region.

	\warning The behavior is undefined if the buffer is not locked
	*/
	virtual
	void
	unlock() const = 0;

	/**
	\brief The size of the buffer

	\return The size of the buffer as a two dimensional size of pixels
	*/
	virtual
	dim const
	size() const = 0;

	/**
	\brief The format used by this surface
	*/
	virtual
	color_format
	format() const = 0;

	/**
	\brief A rectangle describing the size of the buffer

	Returns a rectangle describing the size of the buffer that has its
	position set to zero.

	\return <code> lock_area(lock_area::vector::null(), this->dim()) </code>
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	lock_area const
	area() const;

	/**
	\brief The number of pixels stored in the buffer

	Returns the number of pixels stored in the buffer as a size_type

	\return <code> this->size().content() </code>
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	size_type
	content() const;
};

}
}

#endif
