//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TEXTURE_CONST_BASIC_SCOPED_LOCK_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_CONST_BASIC_SCOPED_LOCK_HPP_INCLUDED

#include <sge/image/box_fwd.hpp>
#include <sge/image/view/const_object_fwd.hpp>
#include <sge/renderer/buffer/const_scoped_lock.hpp>
#include <sge/renderer/buffer/readable_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/texture/basic_lockable_box_fwd.hpp>
#include <sge/renderer/texture/const_basic_scoped_lock_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace texture
{

template<
	typename Tag
>
class const_basic_scoped_lock
{
	FCPPT_NONCOPYABLE(
		const_basic_scoped_lock
	);
public:
	typedef
	sge::renderer::texture::basic_lockable_box<
		Tag
	>
	texture_type;

	typedef
	sge::renderer::buffer::readable<
		Tag
	>
	buffer;

	typedef
	sge::image::box<
		Tag
	>
	lock_area;

	typedef
	sge::image::view::const_object<
		Tag
	>
	const_view;

	SGE_RENDERER_DETAIL_SYMBOL
	explicit
	const_basic_scoped_lock(
		texture_type const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	const_basic_scoped_lock(
		texture_type const &,
		lock_area const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	const_view
	value() const;

	SGE_RENDERER_DETAIL_SYMBOL
	~const_basic_scoped_lock();
private:
	typedef
	sge::renderer::buffer::const_scoped_lock<
		Tag
	>
	buffer_lock;

	buffer_lock const lock_;
};

}
}
}

#endif
