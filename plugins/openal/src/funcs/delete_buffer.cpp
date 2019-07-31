//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/openal/al.hpp>
#include <sge/openal/buffer_id.hpp>
#include <sge/openal/funcs/delete_buffer.hpp>
#include <sge/openal/funcs/delete_buffers.hpp>
#include <fcppt/literal.hpp>


void
sge::openal::funcs::delete_buffer(
	sge::openal::buffer_id const _buffer
)
{
	sge::openal::funcs::delete_buffers(
		&_buffer.get(),
		fcppt::literal<
			ALsizei
		>(
			1
		)
	);

}
