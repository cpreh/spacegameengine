//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/openal/al.hpp>
#include <sge/openal/buffer_id.hpp>
#include <sge/openal/funcs/gen_buffer.hpp>
#include <sge/openal/funcs/gen_buffers.hpp>
#include <fcppt/literal.hpp>

sge::openal::buffer_id sge::openal::funcs::gen_buffer()
{
  ALuint result{};

  sge::openal::funcs::gen_buffers(&result, fcppt::literal<ALsizei>(1));

  return sge::openal::buffer_id(result);
}
