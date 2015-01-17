/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/openal/alc.hpp>
#include <sge/openal/context.hpp>
#include <sge/openal/device.hpp>
#include <sge/openal/logger.hpp>
#include <sge/openal/funcs/alc_create_context.hpp>
#include <sge/openal/funcs/alc_destroy_context.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>


sge::openal::context::context(
	sge::openal::device &_device
)
:
	device_(
		_device
	),
	context_(
		sge::openal::funcs::alc_create_context(
			device_.aldevice()
		)
	)
{
	FCPPT_LOG_DEBUG(
		sge::openal::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("created audio context")
	)
}

ALCcontext &
sge::openal::context::alcontext()
{
	return *context_;
}

ALCdevice &
sge::openal::context::aldevice()
{
	return device_.aldevice();
}

sge::openal::context::~context()
{
	sge::openal::funcs::alc_destroy_context(
		this->aldevice(),
		this->alcontext()
	);

	FCPPT_LOG_DEBUG(
		sge::openal::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("destroyed audio context")
	)
}
