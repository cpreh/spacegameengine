#include "../declare_local_logger.hpp"
#include <sge/cegui/detail/resource_provider.hpp>
#include <sge/cegui/exception.hpp>
#include <sge/cegui/from_cegui_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/assert_message.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fstream>
#include <ios>
#include <cstddef>

SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("resource_provider"))

sge::cegui::detail::resource_provider::resource_provider(
	sge::charconv::system_ptr const _charconv_system)
:
	charconv_system_(
		_charconv_system)
{
}

// This is called for
// - Fonts
// - XML files
void 
sge::cegui::detail::resource_provider::loadRawDataContainer(
	CEGUI::String const &filename, 
	CEGUI::RawDataContainer &output, 
	CEGUI::String const &resource_group)
{
	fcppt::string const
		converted_filename = 
			from_cegui_string(
				filename,
				charconv_system_),
		converted_resource_group = 
			from_cegui_string(
				resource_group,
				charconv_system_);

	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ 
			<< FCPPT_TEXT("loadRawDataContainer(")
			<< converted_filename
			<< FCPPT_TEXT(", ")
			<< converted_resource_group 
			<< FCPPT_TEXT(")"));

	fcppt::filesystem::path const load_path = 
		!converted_resource_group.empty()
		?
			fcppt::filesystem::path(
				converted_resource_group)/converted_filename
		:
			fcppt::filesystem::path(
				converted_filename);

	fcppt::io::cifstream file_stream(
		load_path);

	if(!file_stream.is_open())
		throw exception(
			FCPPT_TEXT("Coudn't open file \"")+
			fcppt::filesystem::path_to_string(
				load_path)+
			FCPPT_TEXT("\""));

	file_stream.seekg(
		0,
		std::ios_base::end);

	std::streampos const filesize = 
		file_stream.tellg();

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
sge::cegui::detail::resource_provider::unloadRawDataContainer(
	CEGUI::RawDataContainer&data)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ 
			<< FCPPT_TEXT("unloadRawDataContainer()"));

	data.release();
}

size_t 
sge::cegui::detail::resource_provider::getResourceGroupFileNames(
	std::vector<CEGUI::String>&,
	CEGUI::String const &file_pattern,
	CEGUI::String const &resource_group)
{
	fcppt::string const
		converted_file_pattern = 
			from_cegui_string(
				file_pattern,
				charconv_system_),
		converted_resource_group = 
			from_cegui_string(
				resource_group,
				charconv_system_);

	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ 
			<< FCPPT_TEXT("loadRawDataContainer(")
			<< converted_file_pattern
			<< FCPPT_TEXT(", ")
			<< converted_resource_group 
			<< FCPPT_TEXT(")"));
	FCPPT_ASSERT_MESSAGE(
		false,
		FCPPT_TEXT("resource_provider::getResourceGroupFilenames not implemented yet!"));
	return 0;
}

sge::cegui::detail::resource_provider::~resource_provider()
{
}
