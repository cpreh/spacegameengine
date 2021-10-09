//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/openal/al.hpp>
#include <sge/openal/buffer_id.hpp>
#include <sge/openal/source_id.hpp>
#include <sge/openal/funcs/source_unqueue_buffer.hpp>
#include <sge/openal/funcs/source_unqueue_buffers_impl.hpp>
#include <fcppt/literal.hpp>

sge::openal::buffer_id
sge::openal::funcs::source_unqueue_buffer(sge::openal::source_id const _source)
{
  ALuint result{0};

  sge::openal::funcs::source_unqueue_buffers_impl(_source, fcppt::literal<ALsizei>(1), &result);

  return sge::openal::buffer_id(result);
}
