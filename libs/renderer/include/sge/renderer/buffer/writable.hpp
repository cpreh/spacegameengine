//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_BUFFER_WRITABLE_HPP_INCLUDED
#define SGE_RENDERER_BUFFER_WRITABLE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/lock_mode_fwd.hpp>
#include <sge/renderer/buffer/readable.hpp>
#include <sge/renderer/buffer/writable_fwd.hpp>
#include <sge/renderer/buffer/traits/view.hpp>
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
	base::format_tag
	format_tag;

	typedef
	typename
	base::format_type
	format_type;

	typedef
	typename
	base::lock_area
	lock_area;

	/**
	\brief The view type

	The view type of nonconst locks
	*/
	typedef
	sge::renderer::buffer::traits::view<
		ImageTag
	>
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
