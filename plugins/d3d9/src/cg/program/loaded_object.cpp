//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
