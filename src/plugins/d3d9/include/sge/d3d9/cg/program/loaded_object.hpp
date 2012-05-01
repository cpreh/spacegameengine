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


#ifndef SGE_D3D9_CG_PROGRAM_LOADED_OBJECT_HPP_INCLUDED
#define SGE_D3D9_CG_PROGRAM_LOADED_OBJECT_HPP_INCLUDED

#include <sge/cg/program/object_fwd.hpp>
#include <sge/renderer/cg/loaded_program.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace d3d9
{
namespace cg
{
namespace program
{

class loaded_object
:
	public sge::renderer::cg::loaded_program
{
	FCPPT_NONCOPYABLE(
		loaded_object
	);
public:
	loaded_object(
		IDirect3DDevice9 *,
		sge::cg::program::object &
	);

	~loaded_object();

	void
	activate() const;

	void
	deactivate() const;
private:
	IDirect3DDevice9 *const device_;

	sge::cg::program::object &program_;
};

}
}
}
}

#endif
