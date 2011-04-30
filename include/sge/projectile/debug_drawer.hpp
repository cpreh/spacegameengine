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


#ifndef SGE_PROJECTILE_DEBUG_DRAWER_HPP_INCLUDED
#define SGE_PROJECTILE_DEBUG_DRAWER_HPP_INCLUDED

#include <sge/projectile/detail/debug_drawer_impl_fwd.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/symbol.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/matrix4.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sge
{
namespace projectile
{
/// bullet offers registering a debug drawer to draw contact points or
/// just shapes. This class implements this interface, caching all the
/// lines and drawing them at once (if you don't do that, it'll be
/// super-slow).
class debug_drawer
{
FCPPT_NONCOPYABLE(
	debug_drawer);
public:	
	SGE_PROJECTILE_SYMBOL explicit
	debug_drawer(
		world &,
		sge::renderer::device &);

	// Updates the line cache
	SGE_PROJECTILE_SYMBOL void
	update();

	// Renders the lines
	SGE_PROJECTILE_SYMBOL void
	render(
		sge::renderer::matrix4 const &);

	SGE_PROJECTILE_SYMBOL void
	active(
		bool);

	SGE_PROJECTILE_SYMBOL bool
	active() const;

	SGE_PROJECTILE_SYMBOL ~debug_drawer();
private:
	fcppt::scoped_ptr<detail::debug_drawer_impl> impl_;
};
}
}

#endif
