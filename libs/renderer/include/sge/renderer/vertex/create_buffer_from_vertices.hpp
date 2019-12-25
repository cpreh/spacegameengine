//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VERTEX_CREATE_BUFFER_FROM_VERTICES_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_CREATE_BUFFER_FROM_VERTICES_HPP_INCLUDED

#include <fcppt/algorithm/range_element_type.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/scoped_lock.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/is_vertex.hpp>
#include <sge/renderer/vf/proxy.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <fcppt/range/begin.hpp>
#include <fcppt/range/end.hpp>
#include <fcppt/range/size.hpp>
#include <fcppt/type_traits/remove_cv_ref_t.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace vertex
{

template<
	typename Format,
	typename Range
>
sge::renderer::vertex::buffer_unique_ptr
create_buffer_from_vertices(
	sge::renderer::device::core &_device,
	sge::renderer::vertex::declaration &_vertex_declaration,
	sge::renderer::resource_flags_field const &_resource_flags,
	Range const &_vertices
)
{
	typedef
	fcppt::type_traits::remove_cv_ref_t<
		fcppt::algorithm::range_element_type<
			Range
		>
	>
	vertex_type;

	static_assert(
		sge::renderer::vf::is_vertex<
			vertex_type
		>::value
	);

	typedef
	typename
	vertex_type::format_part
	format_part;

	sge::renderer::vertex::buffer_unique_ptr buffer{
		_device.create_vertex_buffer(
			sge::renderer::vertex::buffer_parameters(
				_vertex_declaration,
				sge::renderer::vf::dynamic::make_part_index<
					Format,
					format_part
				>(),
				sge::renderer::vertex::count(
					fcppt::range::size(
						_vertices
					)
				),
				_resource_flags
			)
		)
	};

	sge::renderer::vertex::scoped_lock const lock{
		*buffer,
		sge::renderer::lock_mode::writeonly
	};

	typedef
	sge::renderer::vf::view<
		format_part
	>
	view;

	view const dest{
		lock.value()
	};

	std::copy(
		fcppt::range::begin(
			_vertices
		),
		fcppt::range::end(
			_vertices
		),
		dest.begin()
	);

	return
		buffer;
}

}
}
}

#endif
