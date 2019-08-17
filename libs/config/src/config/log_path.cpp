//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/config/app_name.hpp>
#include <sge/config/cache_path.hpp>
#include <sge/config/company_name.hpp>
#include <sge/config/log_path.hpp>
#include <sge/config/impl/try_create_path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


std::filesystem::path
sge::config::log_path(
	sge::config::company_name const &_company_name,
	sge::config::app_name const &_app_name
)
{
	return
		sge::config::impl::try_create_path(
			sge::config::cache_path(
				sge::config::app_name(
					_company_name.get()
				)
			)
		)
		/
		(
			_app_name.get()
			+
			FCPPT_TEXT(".txt")
		);
}
