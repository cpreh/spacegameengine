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


#include <sge/cegui/exception.hpp>
#include <sge/cegui/to_wstring.hpp>
#include <sge/cegui/impl/resource_provider.hpp>
#include <sge/log/default_parameters.hpp>
#include <fcppt/from_std_wstring.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unimplemented_message.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <cstddef>
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
	std::wstring const
		converted_filename(
			sge::cegui::to_wstring(
				filename
			)
		),
		converted_resource_group(
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
	);

	boost::filesystem::path const load_path(
		converted_resource_group.empty()
		?
			boost::filesystem::path(
				converted_filename
			)
		:
			boost::filesystem::path(
				converted_resource_group
			)
			/
			converted_filename
	);

	boost::filesystem::ifstream file_stream(
		load_path,
		std::ios::binary);

	// TODO: filesystem::open
	if(!file_stream.is_open())
		throw sge::cegui::exception(
			FCPPT_TEXT("Coudn't open file \"")+
			fcppt::filesystem::path_to_string(
				load_path)+
			FCPPT_TEXT("\""));

	file_stream.seekg(
		0,
		std::ios_base::end);

	std::streampos const filesize =
		file_stream.tellg();

	// FIXME
	CEGUI::uint8 *data = new CEGUI::uint8[static_cast<std::size_t>(filesize)];

	file_stream.seekg(
		0,
		std::ios_base::beg);

	file_stream.read(
		reinterpret_cast<char*>(
			data),
		static_cast<std::streamsize>(
			filesize));

	output.setData(
		data);
	output.setSize(
		static_cast<std::size_t>(
			filesize));
}

void
sge::cegui::impl::resource_provider::unloadRawDataContainer(
	CEGUI::RawDataContainer &data
)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("unloadRawDataContainer()")
	);

	data.release();
}

size_t
sge::cegui::impl::resource_provider::getResourceGroupFileNames(
	std::vector<CEGUI::String>&,
	CEGUI::String const &file_pattern,
	CEGUI::String const &resource_group)
{
	std::wstring const
		converted_file_pattern(
			sge::cegui::to_wstring(
				file_pattern
			)
		),
		converted_resource_group(
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
	);

	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("resource_provider::getResourceGroupFilenames not implemented yet!")
	);
}

sge::cegui::impl::resource_provider::~resource_provider()
{
}
