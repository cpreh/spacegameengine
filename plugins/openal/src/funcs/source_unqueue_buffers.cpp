//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/openal/buffer_id_container.hpp>
#include <sge/openal/source_id.hpp>
#include <sge/openal/funcs/source_unqueue_buffers.hpp>
#include <sge/openal/funcs/source_unqueue_buffers_impl.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/container/buffer/object_impl.hpp>
#include <fcppt/container/buffer/read_from.hpp>
#include <fcppt/container/buffer/to_raw_vector.hpp>
#include <fcppt/config/external_begin.hpp>
#include <al.h>
#include <fcppt/config/external_end.hpp>

sge::openal::buffer_id_container sge::openal::funcs::source_unqueue_buffers(
    sge::openal::source_id const _source, ALsizei const _size)
{
  return fcppt::container::buffer::to_raw_vector(
      fcppt::container::buffer::read_from<fcppt::container::buffer::object<ALuint>>(
          fcppt::cast::to_unsigned(_size),
          [_source](
              sge::openal::buffer_id_container::pointer const _data,
              sge::openal::buffer_id_container::size_type const _inner_size)
          {
            sge::openal::funcs::source_unqueue_buffers_impl(
                _source, fcppt::cast::size<ALsizei>(fcppt::cast::to_signed(_inner_size)), _data);

            return _inner_size;
          }));
}
