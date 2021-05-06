//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_IMPL_TEXTURE_BASIC_SCOPED_LOCK_IMPL_HPP_INCLUDED
#define SGE_RENDERER_IMPL_TEXTURE_BASIC_SCOPED_LOCK_IMPL_HPP_INCLUDED

#include <sge/image/view/object.hpp>
#include <sge/renderer/basic_dim.hpp>
#include <sge/renderer/basic_lock_box.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/texture/basic_lockable_box.hpp>
#include <sge/renderer/texture/basic_scoped_lock.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/make_ref.hpp>


template<
	typename Tag
>
sge::renderer::texture::basic_scoped_lock<
	Tag
>::basic_scoped_lock(
	texture_ref const _texture,
	sge::renderer::lock_mode const _mode
)
:
	lock_(
		fcppt::make_ref(
			_texture.get().level(
				sge::renderer::texture::mipmap::level(
					0U
				)
			)
		),
		_mode
	)
{
}

template<
	typename Tag
>
sge::renderer::texture::basic_scoped_lock<
	Tag
>::basic_scoped_lock(
	texture_ref const _texture,
	lock_area const &_area,
	sge::renderer::lock_mode const _mode
)
:
	lock_(
		fcppt::make_ref(
			_texture.get().level(
				sge::renderer::texture::mipmap::level(
					0U
				)
			)
		),
		_area,
		_mode
	)
{
}

template<
	typename Tag
>
typename
sge::renderer::texture::basic_scoped_lock<
	Tag
>::view
sge::renderer::texture::basic_scoped_lock<
	Tag
>::value() const
{
	return
		lock_.value();
}

namespace sge::renderer::texture
{
template<
	typename Tag
>
basic_scoped_lock<
	Tag
>::~basic_scoped_lock()
= default;
}

#endif
