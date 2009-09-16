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


#include <sge/config.h>
#ifdef SGE_WINDOWS_PLATFORM
#include "performance_counter_usable.hpp"
#include "query_performance_frequency.hpp"
#include <sge/chrono/exception.hpp>
#include <sge/noncopyable.hpp>

namespace
{

class initializer {
	SGE_NONCOPYABLE(initializer)
public:
	initializer();

	bool
	use_performance_counter() const;
private:
	bool use_performance_counter_;
} instance;

}

bool
sge::chrono::performance_counter_usable()
{
	return instance.use_performance_counter();
}

namespace
{

initializer::initializer()
:
	use_performance_counter_(true)
{
	try
	{
		sge::chrono::query_performance_frequency();
	}
	catch(
		sge::chrono::exception const &
	)
	{
		use_performance_counter_ = false;
	}
}

bool
initializer::use_performance_counter() const
{
	return use_performance_counter_;
}

}

#endif
