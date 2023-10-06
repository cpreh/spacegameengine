//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/openal/buffer_id.hpp>
#include <sge/openal/source_id.hpp>
#include <sge/openal/funcs/source_queue_buffer.hpp>
#include <sge/openal/funcs/source_queue_buffers.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <al.h>
#include <fcppt/config/external_end.hpp>

void sge::openal::funcs::source_queue_buffer(
    sge::openal::source_id const _source, sge::openal::buffer_id const _buffer)
{
  sge::openal::funcs::source_queue_buffers(_source, &_buffer.get(), fcppt::literal<ALsizei>(1));
}
