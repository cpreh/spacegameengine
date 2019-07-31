//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/log/location.hpp>
#include <sge/media/log_location.hpp>
#include <sge/media/impl/log_name.hpp>
#include <fcppt/log/location.hpp>


fcppt::log::location
sge::media::log_location()
{
	return
		sge::log::location()
		/
		sge::media::impl::log_name();
}
