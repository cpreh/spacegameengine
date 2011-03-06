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


#ifndef SGE_D3D9_ONSCREEN_TARGET_HPP_INCLUDED
#define SGE_D3D9_ONSCREEN_TARGET_HPP_INCLUDED

#include "onscreen_target_fwd.hpp"
#include "basic_target.hpp"
#include "d3dinclude.hpp"
#include <sge/renderer/color_surface_ptr.hpp>
#include <sge/renderer/onscreen_target.hpp>
#include <sge/renderer/viewport.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace d3d9
{

class onscreen_target
:
	public d3d9::basic_target<
		sge::renderer::onscreen_target
	>
{
	FCPPT_NONCOPYABLE(
		onscreen_target
	);

	typedef d3d9::basic_target<
		sge::renderer::onscreen_target
	> base;
public:
	onscreen_target(
		IDirect3DDevice9 *,
		sge::renderer::viewport const &
	);

	~onscreen_target();

	renderer::color_surface_ptr const
	surface() const;
};

}
}

#endif
