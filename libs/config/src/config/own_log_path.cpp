//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/config/app_name.hpp>
#include <sge/config/log_path.hpp>
#include <sge/config/own_company_name.hpp>
#include <sge/config/own_log_path.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


boost::filesystem::path
sge::config::own_log_path(
	sge::config::app_name const &_app_name
)
{
	return
		sge::config::log_path(
			sge::config::own_company_name(),
			_app_name
		);
}
