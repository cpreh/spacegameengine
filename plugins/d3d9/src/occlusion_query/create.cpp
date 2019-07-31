//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/occlusion_query/create.hpp>
#include <sge/d3d9/occlusion_query/object.hpp>
#include <sge/renderer/occlusion_query/object.hpp>
#include <sge/renderer/occlusion_query/object_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::renderer::occlusion_query::object_unique_ptr
sge::d3d9::occlusion_query::create(
	IDirect3DDevice9 &_device
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::occlusion_query::object
		>(
			fcppt::make_unique_ptr<
				sge::d3d9::occlusion_query::object
			>(
				_device
			)
		);
}
