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


#include <sge/core/exception.hpp>
#include <sge/plugin/context_base_unique_ptr.hpp>
#include <sge/plugin/file_extension.hpp>
#include <sge/plugin/optional_cache_ref_fwd.hpp>
#include <sge/plugin/detail/context_base_vector.hpp>
#include <sge/plugin/impl/context_base.hpp>
#include <sge/plugin/impl/load_plugins.hpp>
#include <sge/plugin/library/symbol_not_found.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/filesystem/extension_without_dot.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <fcppt/config/external_end.hpp>


sge::plugin::detail::context_base_vector
sge::plugin::impl::load_plugins(
	fcppt::log::object &_log,
	boost::filesystem::path const &_path,
	sge::plugin::optional_cache_ref const &_cache
)
{
	return
		fcppt::algorithm::map_optional<
			sge::plugin::detail::context_base_vector
		>(
			boost::make_iterator_range(
				boost::filesystem::directory_iterator(
					_path
				),
				boost::filesystem::directory_iterator()
			),
			[
				&_log,
				&_cache
			](
				boost::filesystem::path const &_cur_path
			)
			{
				typedef
				fcppt::optional::object<
					sge::plugin::context_base_unique_ptr
				>
				optional_result;

				if(
					boost::filesystem::is_directory(
						_cur_path
					)
					||
					fcppt::filesystem::extension_without_dot(
						_cur_path
					)
					!=
					sge::plugin::file_extension()
				)
				{
					FCPPT_LOG_WARNING(
						_log,
						fcppt::log::out
							<<
							fcppt::filesystem::path_to_string(
								_cur_path
							)
							<<
							FCPPT_TEXT(" does not have the extension ")
							<<
							sge::plugin::file_extension()
							<<
							FCPPT_TEXT(" and thus is ignored!")
					);

					return
						optional_result();
				}

				try
				{
					return
						optional_result(
							fcppt::make_unique_ptr<
								sge::plugin::context_base
							>(
								_cache,
								_cur_path
							)
						);
				}
				catch(
					sge::plugin::library::symbol_not_found const &_exception
				)
				{
					FCPPT_LOG_WARNING(
						_log,
						fcppt::log::out
							<<
							fcppt::filesystem::path_to_string(
								_cur_path
							)
							<<
							FCPPT_TEXT(" doesn't seem to be a valid sge plugin")
							<<
							FCPPT_TEXT(" because the symbol \"")
							<<
							fcppt::from_std_string(
								_exception.symbol()
							)
							<<
							FCPPT_TEXT("\" is missing!")
					);
				}
				catch(
					sge::core::exception const &_exception
				)
				{
					FCPPT_LOG_WARNING(
						_log,
						fcppt::log::out
							<<
							fcppt::filesystem::path_to_string(
								_cur_path
							)
							<<
							FCPPT_TEXT(" failed to load: \"")
							<<
							_exception.string()
							<<
							FCPPT_TEXT("\"!")
					);
				}

				return
					optional_result();
			}
		);
}
