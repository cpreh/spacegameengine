/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/log/context.hpp>
#include <sge/log/object.hpp>
#include <sge/log/parameters/root.hpp>
#include <sge/log/parameters/inherited.hpp>
#include <sge/log/headers.hpp>
#include <sge/mainloop/catch_block.hpp>
#include <sge/optional_impl.hpp>
#include <sge/text.hpp>
#include <sge/cout.hpp>
#include <sge/assert.hpp>

int main()
try
{
	sge::log::context context_;

	sge::log::object logger(
		sge::log::parameters::root(
			sge::cout
		)
		.enabled(
			true
		)
		.context(
			context_
		)
		.prefix(
			SGE_TEXT("sge")
		)
		.level(
			sge::log::level::debug
		)
		.create()
	);

	sge::log::object child_logger(
		sge::log::parameters::inherited(
			logger,
			SGE_TEXT("child")
		)
	);

	sge::log::object *const ref(
		context_.find(
			logger.context_location().location()
		)
	);

	SGE_ASSERT(ref);

	SGE_LOG_INFO(
		*ref,
		sge::log::_
			<< SGE_TEXT("test output!")
	);

	sge::log::object *const child_ref(
		context_.find(
			sge::log::location(
				SGE_TEXT("sge")
			)
			+ SGE_TEXT("child")
		)
	);

	SGE_ASSERT(child_ref);

	SGE_LOG_INFO(
		*child_ref,
		sge::log::_
			<< SGE_TEXT("child output!")
	);
}
SGE_MAINLOOP_CATCH_BLOCK
