//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/core/exception.hpp>
#include <sge/plugin/context_base_unique_ptr.hpp>
#include <sge/plugin/exception.hpp>
#include <sge/plugin/file_extension.hpp>
#include <sge/plugin/optional_cache_ref_fwd.hpp>
#include <sge/plugin/detail/context_base_vector.hpp>
#include <sge/plugin/impl/context_base.hpp>
#include <sge/plugin/impl/load_plugins.hpp>
#include <sge/plugin/library/symbol_not_found.hpp>
#include <fcppt/error_code_to_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/either/to_exception.hpp>
#include <fcppt/filesystem/extension_without_dot.hpp>
#include <fcppt/filesystem/make_directory_range.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <system_error>
#include <fcppt/config/external_end.hpp>


sge::plugin::detail::context_base_vector
sge::plugin::impl::load_plugins(
	fcppt::log::object &_log,
	std::filesystem::path const &_path,
	sge::plugin::optional_cache_ref const &_cache
)
{
	return
		fcppt::algorithm::map_optional<
			sge::plugin::detail::context_base_vector
		>(
			fcppt::either::to_exception(
				fcppt::filesystem::make_directory_range(
					_path,
					std::filesystem::directory_options::none
				),
				[](
					std::error_code const _error
				)
				{
					return
						sge::plugin::exception{
							FCPPT_TEXT("Cannot access plugin directory: ")
							+
							fcppt::error_code_to_string(
								_error
							)
						};
				}
			),
			[
				&_log,
				&_cache
			](
				std::filesystem::path const &_cur_path
			)
			{
				typedef
				fcppt::optional::object<
					sge::plugin::context_base_unique_ptr
				>
				optional_result;

				if(
					std::filesystem::is_directory(
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
					)

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
								std::filesystem::path{
									_cur_path
								}
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
					)
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
					)
				}

				return
					optional_result();
			}
		);
}
