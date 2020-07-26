//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cegui/exception.hpp>
#include <sge/cegui/to_wstring.hpp>
#include <sge/cegui/impl/resource_provider.hpp>
#include <sge/log/default_parameters.hpp>
#include <fcppt/from_std_wstring.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unimplemented_message.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/filesystem/open.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <ios>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>


sge::cegui::impl::resource_provider::resource_provider(
	fcppt::log::object &_log
)
:
	log_{
		_log,
		sge::log::default_parameters(
			fcppt::log::name{
				FCPPT_TEXT("resource_provider")
			}
		)
	}
{
}

// This is called for
// - Fonts
// - XML files
void
sge::cegui::impl::resource_provider::loadRawDataContainer(
	CEGUI::String const &filename,
	CEGUI::RawDataContainer &output,
	CEGUI::String const &resource_group
)
{
	std::wstring const converted_filename(
		sge::cegui::to_wstring(
			filename
		)
	);

	std::wstring const converted_resource_group(
		sge::cegui::to_wstring(
			resource_group
		)
	);

	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<<
			FCPPT_TEXT("loadRawDataContainer(")
			<<
			fcppt::optional::from(
				fcppt::from_std_wstring(
					converted_filename
				),
				[]{
					return
						fcppt::string{
							FCPPT_TEXT("Failed to convert filename")
						};
				}
			)
			<<
			FCPPT_TEXT(", ")
			<<
			fcppt::optional::from(
				fcppt::from_std_wstring(
					converted_resource_group
				),
				[]{
					return
						fcppt::string{
							FCPPT_TEXT("Failed to convert resource group")
						};
				}
			)
			<<
			FCPPT_TEXT(")")
	)

	std::filesystem::path const load_path(
		converted_resource_group.empty()
		?
			std::filesystem::path(
				converted_filename
			)
		:
			std::filesystem::path(
				converted_resource_group
			)
			/
			converted_filename
	);

	std::ifstream file_stream(
		fcppt::optional::to_exception(
			fcppt::filesystem::open<
				std::ifstream
			>(
				load_path,
				std::ios::binary
			),
			[
				&load_path
			]{
				return
					sge::cegui::exception(
						FCPPT_TEXT("Coudn't open file \"")
						+
						fcppt::filesystem::path_to_string(
							load_path
						)
						+
						FCPPT_TEXT("\"")
					);
			}
		)
	);

	file_stream.seekg(
		0,
		std::ios_base::end
	);

	std::streampos const filesize{
		file_stream.tellg()
	};

	// FIXME
	auto *data = new CEGUI::uint8[static_cast<std::size_t>(filesize)];

	file_stream.seekg(
		0,
		std::ios_base::beg
	);

	file_stream.read(
		fcppt::cast::to_char_ptr<
			char *
		>(
			data
		),
		static_cast<
			std::streamsize
		>(
			filesize
		)
	);

	output.setData(
		data
	);

	output.setSize(
		static_cast<
			std::size_t
		>(
			filesize
		)
	);
}

void
sge::cegui::impl::resource_provider::unloadRawDataContainer(
	CEGUI::RawDataContainer &_data
)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("unloadRawDataContainer()")
	)

	_data.release();
}

size_t
sge::cegui::impl::resource_provider::getResourceGroupFileNames(
	std::vector<CEGUI::String> &,
	CEGUI::String const &_file_pattern,
	CEGUI::String const &_resource_group
)
{
	std::wstring const converted_file_pattern(
		sge::cegui::to_wstring(
			_file_pattern
		)
	);

	std::wstring const converted_resource_group(
		sge::cegui::to_wstring(
			_resource_group
		)
	);

	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<<
			FCPPT_TEXT("loadRawDataContainer(")
			<<
			fcppt::optional::from(
				fcppt::from_std_wstring(
					converted_file_pattern
				),
				[]{
					return
						fcppt::string{
							FCPPT_TEXT("Failed to convert file pattern")
						};
				}
			)
			<<
			FCPPT_TEXT(", ")
			<<
			fcppt::optional::from(
				fcppt::from_std_wstring(
					converted_resource_group
				),
				[]{
					return
						fcppt::string{
							FCPPT_TEXT("Failed to convert resource group")
						};
				}
			)
			<<
			FCPPT_TEXT(")")
	)

	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("resource_provider::getResourceGroupFilenames not implemented yet!")
	);
}

sge::cegui::impl::resource_provider::~resource_provider()
= default;
