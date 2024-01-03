//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_BUFFER_SCOPED_LOCK_HPP_INCLUDED
#define SGE_RENDERER_BUFFER_SCOPED_LOCK_HPP_INCLUDED

#include <sge/image/box_fwd.hpp>
#include <sge/renderer/lock_mode_fwd.hpp>
#include <sge/renderer/buffer/scoped_lock_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/buffer/writable_fwd.hpp>
#include <sge/renderer/buffer/traits/view.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>

namespace sge::renderer::buffer
{

/**
\brief Locks a buffer readwrite or writeonly.

\ingroup sge_renderer

Used for locking of buffers readwrite or writeonly. It locks the buffer in the
constructor and unlocks it in the destructor.
*/
template <typename Tag>
class scoped_lock
{
  FCPPT_NONMOVABLE(scoped_lock);

public:
  using buffer_type = sge::renderer::buffer::writable<Tag>;

  using buffer_ref = fcppt::reference<buffer_type>;

  using lock_area = sge::image::box<Tag>;

  using view = sge::renderer::buffer::traits::view<Tag>;

  /**
	\brief Locks an entire buffer

	\param buffer The buffer to lock

	\param mode The lock mode to use

	\warning The behavior is undefined if the buffer is already locked
	*/
  SGE_RENDERER_DETAIL_SYMBOL
  scoped_lock(buffer_ref buffer, sge::renderer::lock_mode mode);

  /**
	\brief Locks a portion of a buffer

	Locks the portion of \a buffer described by \a area

	\param buffer The buffer to lock

	\param area The area to lock

	\param mode The lock mode to use

	\warning The behavior is undefined if the buffer is already locked

	\warning The behavior is undefined if \a area is out of range
	*/
  SGE_RENDERER_DETAIL_SYMBOL
  scoped_lock(buffer_ref buffer, lock_area const &area, sge::renderer::lock_mode mode);

  /**
	\brief Obtain the view of the locked region

	\return The view of the locked region
	*/
  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL view value() const;

  /**
	\brief Unlocks the buffer

	\warning The behavior is undefined if the buffer has been locked again
	or unlocked in between the constructor and destructor
	*/
  SGE_RENDERER_DETAIL_SYMBOL
  ~scoped_lock();

private:
  buffer_ref const buffer_;

  view const view_;
};

}

#endif
