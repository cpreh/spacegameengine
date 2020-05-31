//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_BUFFER_CONST_SCOPED_LOCK_HPP_INCLUDED
#define SGE_RENDERER_BUFFER_CONST_SCOPED_LOCK_HPP_INCLUDED

#include <sge/image/box_fwd.hpp>
#include <sge/renderer/buffer/const_scoped_lock_fwd.hpp>
#include <sge/renderer/buffer/readable_fwd.hpp>
#include <sge/renderer/buffer/traits/const_view.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>


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
	FCPPT_NONMOVABLE(
		const_scoped_lock
	);
public:
	using
	buffer_type
	=
	sge::renderer::buffer::readable<
		Tag
	>;

	using
	buffer_ref
	=
	fcppt::reference<
		buffer_type const
	>;

	using
	lock_area
	=
	sge::image::box<
		Tag
	>;

	using
	const_view
	=
	sge::renderer::buffer::traits::const_view<
		Tag
	>;

	/**
	\brief Locks an entire buffer

	\param buffer The buffer to lock

	\warning The behavior is undefined if the buffer is already locked
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	explicit
	const_scoped_lock(
		buffer_ref buffer
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
		buffer_ref buffer,
		lock_area const &area
	);

	/**
	\brief Obtain the view of the locked region

	\return The view of the locked region
	*/
	[[nodiscard]]
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
	buffer_ref const buffer_;

	const_view const view_;
};

}
}
}

#endif
