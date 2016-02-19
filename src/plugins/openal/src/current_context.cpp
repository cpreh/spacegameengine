/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/openal/context.hpp>
#include <sge/openal/current_context.hpp>
#include <sge/openal/logger.hpp>
#include <sge/openal/funcs/alc_make_context_current.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>


sge::openal::current_context::current_context(
	sge::openal::context &_context
)
:
	context_(
		_context
	)
{
	FCPPT_LOG_DEBUG(
		sge::openal::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("making audio context the current context")
	);

	sge::openal::funcs::alc_make_context_current(
		context_.aldevice(),
		&context_.alcontext()
	);

	FCPPT_LOG_DEBUG(
		sge::openal::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("made audio context the current context")
	);
}

sge::openal::current_context::~current_context()
{
	FCPPT_LOG_DEBUG(
		sge::openal::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("resetting current context")
	);

	sge::openal::funcs::alc_make_context_current(
		context_.aldevice(),
		nullptr
	);
}
