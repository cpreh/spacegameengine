//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/resource_flags_to_pool.hpp>
#include <sge/d3d9/texture/pool.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/texture/capabilities.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <fcppt/container/bitfield/operators.hpp>


D3DPOOL
sge::d3d9::texture::pool(
	sge::renderer::resource_flags_field const &_flags,
	sge::renderer::texture::capabilities_field const &_caps
)
{
	return
		(
			_caps
			&
			sge::renderer::texture::capabilities::render_target
		)
		?
			D3DPOOL_DEFAULT
		:
			sge::d3d9::convert::resource_flags_to_pool(
				_flags
			);
}
