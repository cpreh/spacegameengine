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


#ifndef SGE_RENDERER_BUFFER_READABLE_HPP_INCLUDED
#define SGE_RENDERER_BUFFER_READABLE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/image/traits/box_fwd.hpp>
#include <sge/image/traits/const_view_fwd.hpp>
#include <sge/renderer/buffer/base.hpp>
#include <sge/renderer/buffer/readable_fwd.hpp>
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
class SGE_CORE_DETAIL_CLASS_SYMBOL readable
:
	public
		sge::renderer::buffer::base<
			ImageTag
		>
{
	FCPPT_NONCOPYABLE(
		readable
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	readable();
public:
	SGE_RENDERER_DETAIL_SYMBOL
	~readable()
	override;

	typedef
	sge::renderer::buffer::base<
		ImageTag
	>
	base_type;

	typedef
	typename
	base_type::image_tag
	image_tag;

	typedef
	typename
	base_type::dim
	dim;

	typedef
	typename
	base_type::format_tag
	format_tag;

	typedef
	typename
	base_type::format_type
	format_type;

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
	\brief Locks the whole buffer readonly

	Locks the whole buffer readonly

	\return The view of the locked region

	\warning The behavior is undefined if the buffer is already locked
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	const_view
	lock_c() const;

	/**
	\brief Locks a portion of the buffer readonly

	Reads the portion of the buffer specified by \a area readonly.

	\param area The area to lock

	\return The view of the locked region

	\warning The behavior is undefined if the buffer is already locked

	\warning The behavior is undefined if \a area is out of range
	*/
	virtual
	const_view
	lock_c(
		lock_area const &area
	) const = 0;

	/**
	\brief Unlocks the buffer

	Unlocks the currently locked buffer region.

	\warning The behavior is undefined if the buffer is not locked
	*/
	virtual
	void
	unlock() const = 0;
};

}
}
}

#endif
