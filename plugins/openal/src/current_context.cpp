//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/openal/context.hpp>
#include <sge/openal/current_context.hpp>
#include <sge/openal/funcs/alc_make_context_current.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/log/out.hpp>


sge::openal::current_context::current_context(
	fcppt::log::object_reference const _log,
	fcppt::reference<
		sge::openal::context
	> const _context
)
:
	log_{
		_log
	},
	context_(
		_context
	)
{
	FCPPT_LOG_DEBUG(
		log_.get(),
		fcppt::log::out
			<< FCPPT_TEXT("making audio context the current context")
	)

	sge::openal::funcs::alc_make_context_current(
		fcppt::make_ref(
			context_.get().aldevice()
		),
		&context_.get().alcontext()
	);

	FCPPT_LOG_DEBUG(
		log_.get(),
		fcppt::log::out
			<< FCPPT_TEXT("made audio context the current context")
	)
}

sge::openal::current_context::~current_context()
{
	FCPPT_LOG_DEBUG(
		log_.get(),
		fcppt::log::out
			<< FCPPT_TEXT("resetting current context")
	)

	sge::openal::funcs::alc_make_context_current(
		fcppt::make_ref(
			context_.get().aldevice()
		),
		nullptr
	);
}
