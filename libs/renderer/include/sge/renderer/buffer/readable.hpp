//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_BUFFER_READABLE_HPP_INCLUDED
#define SGE_RENDERER_BUFFER_READABLE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/image/box_fwd.hpp>
#include <sge/renderer/buffer/base.hpp>
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
	sge::image::box<
		ImageTag
	>
	lock_area;

	/**
	\brief The const view type

	The view type of const locks
	*/
	typedef
	sge::renderer::buffer::traits::const_view<
		ImageTag
	>
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
