//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/openal/al.hpp>
#include <sge/openal/buffer_id_container.hpp>
#include <sge/openal/funcs/gen_buffers.hpp>
#include <sge/openal/funcs/gen_multi_buffers.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/container/buffer/object_impl.hpp>
#include <fcppt/container/buffer/read_from.hpp>
#include <fcppt/container/buffer/to_raw_vector.hpp>


sge::openal::buffer_id_container
sge::openal::funcs::gen_multi_buffers(
	sge::openal::buffer_id_container::size_type const _size
)
{
	return
		fcppt::container::buffer::to_raw_vector(
			fcppt::container::buffer::read_from<
				fcppt::container::buffer::object<
					sge::openal::buffer_id_container::value_type
				>
			>(
				_size,
				[](
					sge::openal::buffer_id_container::pointer const _data,
					sge::openal::buffer_id_container::size_type const _inner_size
				)
				{
					sge::openal::funcs::gen_buffers(
						_data,
						fcppt::cast::size<
							ALsizei
						>(
							fcppt::cast::to_signed(
								_inner_size
							)
						)
					);

					return
						_inner_size;
				}
			)
		);
}
