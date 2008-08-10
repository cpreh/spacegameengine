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


#include <sge/renderer/const_scoped_texture_lock.hpp>

sge::renderer::const_scoped_texture_lock::const_scoped_texture_lock(
	const_texture_ptr const tex_)
: tex_(tex_),
  value_(tex_->lock())
{}

sge::renderer::const_scoped_texture_lock::const_scoped_texture_lock(
	const_texture_ptr const tex_,
	lock_rect const &r)
: tex_(tex_),
  value_(tex_->lock(r))
{}

sge::renderer::const_scoped_texture_lock::~const_scoped_texture_lock()
{
	tex_->unlock();
}

sge::renderer::const_image_view const
sge::renderer::const_scoped_texture_lock::value() const
{
	return value_;
}
