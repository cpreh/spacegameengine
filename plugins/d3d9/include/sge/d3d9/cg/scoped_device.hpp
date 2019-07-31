//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_CG_SCOPED_DEVICE_HPP_INCLUDED
#define SGE_D3D9_CG_SCOPED_DEVICE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/cg/scoped_device_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace d3d9
{
namespace cg
{

class scoped_device
{
	FCPPT_NONCOPYABLE(
		scoped_device
	);
public:
	explicit
	scoped_device(
		IDirect3DDevice9 &
	);

	~scoped_device();
private:
	IDirect3DDevice9 *const old_;

	bool const needs_reset_;
};

}
}
}

#endif
