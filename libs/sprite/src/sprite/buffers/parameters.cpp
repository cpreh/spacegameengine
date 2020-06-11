//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/sprite/buffers/parameters.hpp>


sge::sprite::buffers::parameters::parameters(
	sge::renderer::device::core_ref const _device,
	sge::renderer::vertex::const_declaration_ref const _vertex_declaration
)
:
	device_(
		_device
	),
	vertex_declaration_(
		_vertex_declaration
	)
{
}

sge::renderer::device::core &
sge::sprite::buffers::parameters::device() const
{
	return
		device_.get();
}

sge::renderer::vertex::declaration const &
sge::sprite::buffers::parameters::vertex_declaration() const
{
	return
		vertex_declaration_.get();
}
