/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/projectile/detail/symbol.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/detail/debug_drawer_impl_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


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
	SGE_PROJECTILE_DETAIL_SYMBOL
	debug_drawer(
		sge::projectile::world &,
		sge::renderer::device::core &);

	// Updates the line cache
	SGE_PROJECTILE_DETAIL_SYMBOL void
	update();

	// Renders the lines
	SGE_PROJECTILE_DETAIL_SYMBOL void
	render(
		sge::renderer::context::core &);

	SGE_PROJECTILE_DETAIL_SYMBOL void
	active(
		bool);

	SGE_PROJECTILE_DETAIL_SYMBOL bool
	active() const;

	SGE_PROJECTILE_DETAIL_SYMBOL ~debug_drawer();
private:
	std::unique_ptr<detail::debug_drawer_impl> const impl_;
};
}
}

#endif
