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


#ifndef SGE_SRC_RENDERER_TEXTURE_BASIC_LOCKABLE_BOX_IMPL_HPP_INCLUDED
#define SGE_SRC_RENDERER_TEXTURE_BASIC_LOCKABLE_BOX_IMPL_HPP_INCLUDED

#include <sge/renderer/basic_dim.hpp>
#include <sge/renderer/buffer/readable.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/basic_lockable_box.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>


template<
	typename Tag
>
sge::renderer::texture::basic_lockable_box<
	Tag
>::basic_lockable_box()
:
	sge::renderer::texture::base()
{
}

template<
	typename Tag
>
sge::renderer::texture::basic_lockable_box<
	Tag
>::~basic_lockable_box()
{
}

template<
	typename Tag
>
typename
sge::renderer::texture::basic_lockable_box<
	Tag
>::dim
sge::renderer::texture::basic_lockable_box<
	Tag
>::size() const
{
	return
		this->level(
			sge::renderer::texture::mipmap::level(
				0u
			)
		).size();
}

#endif
