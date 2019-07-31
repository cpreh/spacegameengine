//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_SURFACE_DEPTH_STENCIL_ONSCREEN_HPP_INCLUDED
#define SGE_D3D9_SURFACE_DEPTH_STENCIL_ONSCREEN_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/resource.hpp>
#include <sge/d3d9/surface/optional_d3d_ref.hpp>
#include <sge/d3d9/surface/optional_d3d_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace d3d9
{
namespace surface
{

class depth_stencil_onscreen
:
	public sge::d3d9::resource
{
	FCPPT_NONCOPYABLE(
		depth_stencil_onscreen
	);
public:
	explicit
	depth_stencil_onscreen(
		IDirect3DDevice9 &
	);

	~depth_stencil_onscreen()
	override;

	sge::d3d9::surface::optional_d3d_ref
	surface() const;
private:
	void
	init();

	void
	on_loss()
	override;

	void
	on_reset()
	override;

	IDirect3DDevice9 &device_;

	sge::d3d9::surface::optional_d3d_unique_ptr surface_;
};

}
}
}

#endif
