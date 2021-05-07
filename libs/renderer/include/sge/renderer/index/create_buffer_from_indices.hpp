//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_CREATE_BUFFER_FROM_INDICES_HPP_INCLUDED
#define SGE_RENDERER_INDEX_CREATE_BUFFER_FROM_INDICES_HPP_INCLUDED

#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/index/buffer.hpp>
#include <sge/renderer/index/buffer_parameters.hpp>
#include <sge/renderer/index/buffer_unique_ptr.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/format.hpp>
#include <sge/renderer/index/iterator.hpp>
#include <sge/renderer/index/nonconst_tag.hpp>
#include <sge/renderer/index/scoped_lock.hpp>
#include <sge/renderer/index/dynamic/make_format.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/algorithm/range_element_type.hpp>
#include <fcppt/range/begin.hpp>
#include <fcppt/range/end.hpp>
#include <fcppt/range/size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace index
{

template<
	typename Range
>
sge::renderer::index::buffer_unique_ptr
create_buffer_from_indices(
	sge::renderer::device::core_ref const _device,
	sge::renderer::resource_flags_field const &_resource_flags,
	Range const &_range
)
{
	using
	index_type
	=
	std::remove_cvref_t<
		fcppt::algorithm::range_element_type<
			Range
		>
	>;

	using
	format
	=
	sge::renderer::index::format<
		index_type
	>;

	sge::renderer::index::buffer_unique_ptr buffer(
		_device.get().create_index_buffer(
			sge::renderer::index::buffer_parameters(
				sge::renderer::index::dynamic::make_format<
					format
				>(),
				sge::renderer::index::count(
					fcppt::range::size(
						_range
					)
				),
				_resource_flags
			)
		)
	);

	sge::renderer::index::scoped_lock const lock{
		fcppt::make_ref(
			*buffer
		),
		sge::renderer::lock_mode::writeonly
	};

	std::copy(
		fcppt::range::begin(
			_range
		),
		fcppt::range::end(
			_range
		),
		sge::renderer::index::iterator<
			format,
			sge::renderer::index::nonconst_tag
		>{
			lock.value().data()
		}
	);

	return
		buffer;
}

}
}
}

#endif
