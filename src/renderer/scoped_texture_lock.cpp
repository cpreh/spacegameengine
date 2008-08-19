/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/renderer/instantiate_scoped_lock.hpp>
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>

sge::renderer::scoped_texture_lock_wrapper const
sge::renderer::make_scoped_lock(
	texture_ptr const t,
	lock_flag_t const flags)
{
	return scoped_texture_lock_wrapper(
		t,
		t->lock(flags));
}

sge::renderer::scoped_texture_lock_wrapper const
sge::renderer::make_scoped_lock(
	texture_ptr const t,
	lock_rect const &r,
	lock_flag_t const flags)
{
	return scoped_texture_lock_wrapper(
		t,
		t->lock(r, flags));
}

sge::renderer::const_scoped_texture_lock_wrapper const
sge::renderer::make_scoped_lock(
	const_texture_ptr const t,
	lock_rect const &r)
{
	return const_scoped_texture_lock_wrapper(
		t,
		t->lock(r));
}

SGE_RENDERER_INSTANTIATE_SCOPED_LOCK(
	sge::renderer::texture_ptr,
	sge::renderer::image_view)

SGE_RENDERER_INSTANTIATE_SCOPED_LOCK(
	sge::renderer::const_texture_ptr,
	sge::renderer::const_image_view)
