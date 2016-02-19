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


#ifndef SGE_D3D9_TARGET_BASIC_HPP_INCLUDED
#define SGE_D3D9_TARGET_BASIC_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/target/base.hpp>
#include <sge/renderer/caps/target_surface_indices.hpp>
#include <sge/renderer/clear/parameters_fwd.hpp>
#include <sge/renderer/target/scissor_area.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace d3d9
{
namespace target
{

template<
	typename Base
>
class basic
:
	public Base,
	public sge::d3d9::target::base
{
	FCPPT_NONCOPYABLE(
		basic
	);
protected:
	basic(
		IDirect3DDevice9 &,
		sge::renderer::target::viewport const &,
		sge::renderer::caps::target_surface_indices
	);
public:
	~basic()
	override;
private:
	void
	viewport(
		sge::renderer::target::viewport const &
	);

	sge::renderer::target::viewport
	viewport() const
	override;

	void
	scissor_area(
		sge::renderer::target::scissor_area const &
	)
	override;

	sge::renderer::target::scissor_area
	scissor_area() const
	override;

	void
	clear(
		sge::renderer::clear::parameters const &
	)
	override;

	void
	active(
		bool
	)
	override;
protected:
	IDirect3DDevice9 &
	device() const;
private:
	void
	check_viewport();

	void
	check_scissor_area();

	virtual
	void
	on_activate() = 0;

	virtual
	void
	on_deactivate() = 0;

	IDirect3DDevice9 &device_;

	sge::renderer::caps::target_surface_indices const max_surfaces_;

	bool active_;

	sge::renderer::target::viewport viewport_;

	sge::renderer::target::scissor_area scissor_area_;
};

}
}
}

#endif
