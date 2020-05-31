//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TEXTURE_BASIC_SCOPED_LOCK_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_BASIC_SCOPED_LOCK_HPP_INCLUDED

#include <sge/image/box_fwd.hpp>
#include <sge/image/view/object_fwd.hpp>
#include <sge/renderer/lock_mode_fwd.hpp>
#include <sge/renderer/buffer/scoped_lock.hpp>
#include <sge/renderer/buffer/writable_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/texture/basic_lockable_box_fwd.hpp>
#include <sge/renderer/texture/basic_scoped_lock_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace texture
{

template<
	typename Tag
>
class basic_scoped_lock
{
	FCPPT_NONMOVABLE(
		basic_scoped_lock
	);
public:
	using
	texture_type
	=
	sge::renderer::texture::basic_lockable_box<
		Tag
	>;

	using
	texture_ref
	=
	fcppt::reference<
		texture_type
	>;

	using
	buffer
	=
	sge::renderer::buffer::writable<
		Tag
	>;

	using
	lock_area
	=
	sge::image::box<
		Tag
	>;

	using
	view
	=
	sge::image::view::object<
		Tag
	>;

	SGE_RENDERER_DETAIL_SYMBOL
	basic_scoped_lock(
		texture_ref,
		sge::renderer::lock_mode
	);

	SGE_RENDERER_DETAIL_SYMBOL
	basic_scoped_lock(
		texture_ref,
		lock_area const &,
		sge::renderer::lock_mode
	);

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	view
	value() const;

	SGE_RENDERER_DETAIL_SYMBOL
	~basic_scoped_lock();
private:
	using
	buffer_lock
	=
	sge::renderer::buffer::scoped_lock<
		Tag
	>;

	buffer_lock const lock_;
};

}
}
}

#endif
