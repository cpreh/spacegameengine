/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_D3D9_BASIC_TARGET_HPP_INCLUDED
#define SGE_D3D9_BASIC_TARGET_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/target_base.hpp>
#include <sge/renderer/scissor_area.hpp>
#include <sge/renderer/viewport.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/box/basic_decl.hpp>


namespace sge
{
namespace d3d9
{

template<
	typename Base
>
class basic_target
:
	public Base,
	public d3d9::target_base
{
	FCPPT_NONCOPYABLE(
		basic_target
	);
public:
	basic_target(
		IDirect3DDevice9 *,
		sge::renderer::viewport const &
	);

	~basic_target();

	void
	viewport(
		renderer::viewport const &
	);

	renderer::viewport const
	viewport() const;

	void
	scissor_area(
		renderer::scissor_area const &
	);

	renderer::scissor_area const
	scissor_area() const;

	void
	active(
		bool
	);
protected:
	IDirect3DDevice9 *
	device() const;
private:
	void
	check_viewport();

	void
	check_scissor_area();

	virtual void
	on_activate() = 0;

	virtual void
	on_deactivate() = 0;

	IDirect3DDevice9 *const device_;

	bool active_;

	renderer::viewport viewport_;

	renderer::scissor_area scissor_area_;
};

}
}

#endif
