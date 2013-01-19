/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/cg/check_state.hpp>
#include <sge/cg/program/object.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/cg/scoped_device.hpp>
#include <sge/d3d9/cg/program/loaded_object.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <Cg/cgD3D9.h>
#include <fcppt/config/external_end.hpp>


sge::d3d9::cg::program::loaded_object::loaded_object(
	IDirect3DDevice9 &_device,
	sge::cg::program::object &_program
)
:
	device_(
		_device
	),
	program_(
		_program
	)
{
	sge::d3d9::cg::scoped_device const context(
		device_
	);

	if(
		::cgD3D9LoadProgram(
			program_.get(),
			CG_FALSE,
			0u
		)
		!=
		D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("cgD3D9LoadProgram failed")
		);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgD3D9LoadProgram failed"),
		sge::renderer::exception
	)
}

sge::d3d9::cg::program::loaded_object::~loaded_object()
{
	sge::d3d9::cg::scoped_device const context(
		device_
	);

	if(
		::cgD3D9UnloadProgram(
			program_.get()
		)
		!=
		D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("cgD3D9UnloadProgram failed")
		);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgD3D9UnloadProgram failed"),
		sge::renderer::exception
	)
}

void
sge::d3d9::cg::program::loaded_object::activate() const
{
	sge::d3d9::cg::scoped_device const context(
		device_
	);

	if(
		::cgD3D9BindProgram(
			program_.get()
		)
		!=
		D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("cgD3D9BindProgram failed")
		);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgD3D9BindProgram failed"),
		sge::renderer::exception
	)
}

void
sge::d3d9::cg::program::loaded_object::deactivate() const
{
	sge::d3d9::cg::scoped_device const context(
		device_
	);

	if(
		::cgD3D9UnbindProgram(
			program_.get()
		)
		!=
		D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("cgD3D9UnbindProgram failed")
		);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgD3D9UnbindProgram failed"),
		sge::renderer::exception
	)
}
