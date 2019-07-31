//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/create_query.hpp>
#include <sge/d3d9/occlusion_query/object.hpp>
#include <sge/d3d9/queryfuncs/get_dword.hpp>
#include <sge/d3d9/queryfuncs/issue.hpp>
#include <sge/renderer/occlusion_query/blocking_wait.hpp>
#include <sge/renderer/occlusion_query/object.hpp>
#include <sge/renderer/occlusion_query/optional_pixel_count.hpp>
#include <sge/renderer/occlusion_query/pixel_count.hpp>
#include <fcppt/optional/map.hpp>


sge::d3d9::occlusion_query::object::object(
	IDirect3DDevice9 &_device
)
:
	sge::renderer::occlusion_query::object(),
	query_(
		sge::d3d9::devicefuncs::create_query(
			_device,
			D3DQUERYTYPE_OCCLUSION
		)
	)
{
}

sge::d3d9::occlusion_query::object::~object()
{
}

void
sge::d3d9::occlusion_query::object::begin()
{
	sge::d3d9::queryfuncs::issue(
		*query_,
		D3DISSUE_BEGIN
	);
}

void
sge::d3d9::occlusion_query::object::end()
{
	sge::d3d9::queryfuncs::issue(
		*query_,
		D3DISSUE_END
	);
}

sge::renderer::occlusion_query::optional_pixel_count
sge::d3d9::occlusion_query::object::result(
	sge::renderer::occlusion_query::blocking_wait const _block
) const
{
	return
		fcppt::optional::map(
			sge::d3d9::queryfuncs::get_dword(
				*query_,
				_block.get()
				?
					D3DGETDATA_FLUSH
				:
					0u
			),
			[](
				DWORD const _value
			)
			{
				return
					sge::renderer::occlusion_query::pixel_count(
						_value
					);
			}
		);
}
