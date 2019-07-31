//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_TARGET_BASIC_IMPL_HPP_INCLUDED
#define SGE_D3D9_TARGET_BASIC_IMPL_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/clear.hpp>
#include <sge/d3d9/devicefuncs/set_scissor_rect.hpp>
#include <sge/d3d9/devicefuncs/set_viewport.hpp>
#include <sge/d3d9/target/base.hpp>
#include <sge/d3d9/target/basic.hpp>
#include <sge/d3d9/target/temporary.hpp>
#include <sge/renderer/caps/target_surface_indices.hpp>
#include <sge/renderer/clear/parameters_fwd.hpp>
#include <sge/renderer/target/scissor_area.hpp>
#include <sge/renderer/target/viewport.hpp>


template<
	typename Base
>
sge::d3d9::target::basic<
	Base
>::basic(
	IDirect3DDevice9 &_device,
	sge::renderer::target::viewport const &_viewport,
	sge::renderer::caps::target_surface_indices const _max_surfaces
)
:
	Base(),
	sge::d3d9::target::base(),
	device_(
		_device
	),
	max_surfaces_(
		_max_surfaces
	),
	active_(
		false
	),
	viewport_(
		_viewport
	),
	scissor_area_(
		sge::renderer::target::scissor_area(
			_viewport.get()
		)
	)
{
}

template<
	typename Base
>
sge::d3d9::target::basic<
	Base
>::~basic()
{
}

template<
	typename Base
>
void
sge::d3d9::target::basic<
	Base
>::viewport(
	sge::renderer::target::viewport const &_viewport
)
{
	viewport_ = _viewport;

	this->check_viewport();
}

template<
	typename Base
>
sge::renderer::target::viewport
sge::d3d9::target::basic<
	Base
>::viewport() const
{
	return viewport_;
}

template<
	typename Base
>
void
sge::d3d9::target::basic<
	Base
>::scissor_area(
	sge::renderer::target::scissor_area const &_scissor_area
)
{
	scissor_area_ = _scissor_area;

	this->check_scissor_area();
}

template<
	typename Base
>
sge::renderer::target::scissor_area
sge::d3d9::target::basic<
	Base
>::scissor_area() const
{
	return scissor_area_;
}

template<
	typename Base
>
void
sge::d3d9::target::basic<
	Base
>::clear(
	sge::renderer::clear::parameters const &_parameters
)
{
	sge::d3d9::target::temporary const scoped_target(
		device_,
		max_surfaces_
	);

	sge::d3d9::devicefuncs::clear(
		device_,
		_parameters
	);
}

template<
	typename Base
>
void
sge::d3d9::target::basic<
	Base
>::active(
	bool const _active
)
{
	active_ = _active;

	this->check_viewport();

	this->check_scissor_area();

	if(
		_active
	)
		this->on_activate();
	else
		this->on_deactivate();
}

template<
	typename Base
>
IDirect3DDevice9 &
sge::d3d9::target::basic<
	Base
>::device() const
{
	return device_;
}

template<
	typename Base
>
void
sge::d3d9::target::basic<
	Base
>::check_viewport()
{
	if(
		active_
	)
		sge::d3d9::devicefuncs::set_viewport(
			device_,
			viewport_
		);
}

template<
	typename Base
>
void
sge::d3d9::target::basic<
	Base
>::check_scissor_area()
{
	if(
		active_
	)
		sge::d3d9::devicefuncs::set_scissor_rect(
			device_,
			scissor_area_
		);
}

#endif
