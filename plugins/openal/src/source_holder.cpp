//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/openal/source_holder.hpp>
#include <sge/openal/source_id.hpp>
#include <sge/openal/funcs/delete_source.hpp>
#include <sge/openal/funcs/gen_source.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>


sge::openal::source_holder::source_holder(
	fcppt::log::object &_log
)
:
	log_{
		_log
	},
	value_(
		sge::openal::funcs::gen_source()
	)
{
}

sge::openal::source_holder::~source_holder()
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("Deleting a source")
	)

	sge::openal::funcs::delete_source(
		value_
	);
}

sge::openal::source_id
sge::openal::source_holder::get() const
{
	return
		value_;
}
