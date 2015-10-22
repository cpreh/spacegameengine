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


#ifndef SGE_RENDERER_BUFFER_WRITABLE_HPP_INCLUDED
#define SGE_RENDERER_BUFFER_WRITABLE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/image/traits/view_fwd.hpp>
#include <sge/renderer/lock_mode_fwd.hpp>
#include <sge/renderer/buffer/readable.hpp>
#include <sge/renderer/buffer/writable_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace buffer
{

template<
	typename ImageTag
>
class SGE_CORE_DETAIL_CLASS_SYMBOL writable
:
	public
		sge::renderer::buffer::readable<
			ImageTag
		>
{
	FCPPT_NONCOPYABLE(
		writable
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	writable();
public:
	SGE_RENDERER_DETAIL_SYMBOL
	~writable()
	override;

	typedef
	sge::renderer::buffer::readable<
		ImageTag
	>
	base;

	typedef
	typename
	base::image_tag
	image_tag;

	typedef
	typename
	base::dim
	dim;

	typedef
	typename
	base::color_tag
	color_tag;

	typedef
	typename
	base::color_format
	color_format;

	typedef
	typename
	base::lock_area
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
	\brief Locks the whole buffer readwrite or writeonly

	Locks the whole buffer readwrite or writeonly, depending on \a mode.

	\param mode Tells if the buffer should be locked readwrite or writeonly

	\return The view of the locked region

	\warning The behavior is undefined if the buffer is already locked
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	view
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
	view
	lock(
		lock_area const &area,
		sge::renderer::lock_mode mode
	) = 0;
};

}
}
}

#endif
