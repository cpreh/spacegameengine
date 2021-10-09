//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/openal/al.hpp>
#include <sge/openal/buffer_id_container.hpp>
#include <sge/openal/funcs/delete_buffers.hpp>
#include <sge/openal/funcs/delete_multi_buffers.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>

void sge::openal::funcs::delete_multi_buffers(sge::openal::buffer_id_container const &_ids)
{
  sge::openal::funcs::delete_buffers(
      _ids.data(), fcppt::cast::size<ALsizei>(fcppt::cast::to_signed(_ids.size())));
}
