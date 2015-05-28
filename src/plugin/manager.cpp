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


#include <sge/core/exception.hpp>
#include <sge/plugin/file_extension.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/optional_cache_ref_fwd.hpp>
#include <sge/plugin/library/symbol_not_found.hpp>
#include <sge/src/plugin/context_base.hpp>
#include <sge/src/plugin/logger.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_enum_range.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/extension_without_dot.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <fcppt/config/external_end.hpp>


sge::plugin::manager::manager(
	boost::filesystem::path const &_path,
	sge::plugin::optional_cache_ref const &_cache
)
:
	// TODO: Direct initialization
	plugins_(),
	categories_()
{
	FCPPT_LOG_DEBUG(
		sge::plugin::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("Scanning for plugins in ")
			<< fcppt::filesystem::path_to_string(
				_path
			)
	);

	for(
		boost::filesystem::path const &path
		:
		boost::make_iterator_range(
			boost::filesystem::directory_iterator(
				_path
			),
			boost::filesystem::directory_iterator()
		)
	)
	{
		if(
			boost::filesystem::is_directory(
				path
			)
			||
			fcppt::filesystem::extension_without_dot(
				path
			)
			!=
			sge::plugin::file_extension()
		)
		{
			FCPPT_LOG_WARNING(
				sge::plugin::logger(),
				fcppt::log::_
					<< fcppt::filesystem::path_to_string(
						path
					)
					<< FCPPT_TEXT(" does not have the extension ")
					<< sge::plugin::file_extension()
					<< FCPPT_TEXT(" and thus is ignored!")
			);

			continue;
		}

		try
		{
			plugins_.push_back(
				fcppt::make_unique_ptr_fcppt<
					sge::plugin::context_base
				>(
					_cache,
					path
				)
			);
		}
		catch(
			sge::plugin::library::symbol_not_found const &_exception
		)
		{
			FCPPT_LOG_WARNING(
				sge::plugin::logger(),
				fcppt::log::_
					<< fcppt::filesystem::path_to_string(
						path
					)
					<< FCPPT_TEXT(" doesn't seem to be a valid sge plugin")
					<< FCPPT_TEXT(" because the symbol \"")
					<< fcppt::from_std_string(
						_exception.symbol()
					)
					<< FCPPT_TEXT("\" is missing!")
			);
		}
		catch(
			sge::core::exception const &_exception
		)
		{
			FCPPT_LOG_WARNING(
				sge::plugin::logger(),
				fcppt::log::_
					<< fcppt::filesystem::path_to_string(
						path
					)
					<< FCPPT_TEXT(" failed to load: \"")
					<< _exception.string()
					<< FCPPT_TEXT("\"!")
			);
		}
	}

	for(
		sge::plugin::context_base_unique_ptr const &context
		:
		plugins_
	)
		for(
			auto index
			:
			fcppt::make_enum_range<
				sge::plugin::capabilities
			>()
		)
			if(
				context->info().capabilities()
				&
				index
			)
				categories_[
					index
				].push_back(
					context.get_pointer()
				);
}

sge::plugin::manager::~manager()
{
}
