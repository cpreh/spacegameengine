//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_BUFFERS_ALLOCATE_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_ALLOCATE_HPP_INCLUDED

#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/buffers/object.hpp>
#include <sge/sprite/detail/buffers/allocate.hpp>


namespace sge::sprite::buffers
{

template<
	typename Choices
>
inline
sge::sprite::buffers::object<
	Choices
>
allocate(
	sge::renderer::device::core_ref const _renderer,
	sge::renderer::vertex::const_declaration_ref const _vertex_declaration,
	sge::sprite::count const _num_sprites,
	sge::renderer::resource_flags_field const &_resource_flags
)
{
	return
		sge::sprite::detail::buffers::allocate<
			Choices
		>(
			_renderer,
			_vertex_declaration,
			_num_sprites,
			_resource_flags
		);
}

}

#endif
