//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/openal/buffer_holder.hpp>
#include <sge/openal/buffer_id.hpp>
#include <sge/openal/funcs/delete_buffer.hpp>
#include <sge/openal/funcs/gen_buffer.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>


sge::openal::buffer_holder::buffer_holder(
	fcppt::log::object &_log
)
:
	log_{
		_log
	},
	buffer_(
		sge::openal::funcs::gen_buffer()
	)
{
}

sge::openal::buffer_holder::~buffer_holder()
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("Deleting a buffer")
	)

	sge::openal::funcs::delete_buffer(
		buffer_
	);
}

sge::openal::buffer_id
sge::openal::buffer_holder::get() const
{
	return
		buffer_;
}
