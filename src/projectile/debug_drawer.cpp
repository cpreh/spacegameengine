/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/projectile/debug_drawer.hpp>
#include <sge/src/projectile/detail/debug_drawer_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>


sge::projectile::debug_drawer::debug_drawer(
	world &_world,
	sge::renderer::device &_renderer)
:
	impl_(
		fcppt::make_unique_ptr<detail::debug_drawer_impl>(
			fcppt::ref(
				_world),
			fcppt::ref(
				_renderer)))
{
}

void
sge::projectile::debug_drawer::update()
{
	impl_->update();
}

void
sge::projectile::debug_drawer::render(
	sge::renderer::matrix4 const &mvp)
{
	impl_->render(
		mvp);
}

void
sge::projectile::debug_drawer::active(
	bool const _active)
{
	impl_->active(
		_active);
}

bool
sge::projectile::debug_drawer::active() const
{
	return impl_->active();
}

sge::projectile::debug_drawer::~debug_drawer()
{
}
