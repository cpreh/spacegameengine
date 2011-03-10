#include "declare_local_logger.hpp"
#include <sge/cegui/resource_provider.hpp>
#include <sge/cegui/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert_message.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fstream>
#include <iostream>
#include <ios>
#include <cstddef>

SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("resource_provider"))

sge::cegui::resource_provider::resource_provider(
	fcppt::filesystem::path const &_prefix)
:
	prefix_(
		_prefix)
{
}

// This is called for
// - Fonts
// - XML files
void 
sge::cegui::resource_provider::loadRawDataContainer(
	CEGUI::String const &filename, 
	CEGUI::RawDataContainer &output, 
	CEGUI::String const&resourceGroup)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ 
			<< FCPPT_TEXT("loadRawDataContainer(")
			<< fcppt::from_std_string(filename.c_str())
			<< FCPPT_TEXT(", ")
			<< fcppt::from_std_string(resourceGroup.c_str())
			<< FCPPT_TEXT(")"));

	fcppt::io::cifstream file_stream(
		prefix_ 
			/ fcppt::from_std_string(filename.c_str()));

	if(!file_stream.is_open())
		throw exception(
			FCPPT_TEXT("Coudn't open file \"")+
			fcppt::from_std_string(
				filename.c_str())+
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
sge::cegui::resource_provider::unloadRawDataContainer(
	CEGUI::RawDataContainer&data)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ 
			<< FCPPT_TEXT("unloadRawDataContainer()"));

	data.release();
}

size_t 
sge::cegui::resource_provider::getResourceGroupFileNames(
	std::vector<CEGUI::String>&,
	CEGUI::String const &file_pattern,
	CEGUI::String const &resource_group)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ 
			<< FCPPT_TEXT("getResourceGroupFileNames(")
			<< fcppt::from_std_string(file_pattern.c_str())
			<< FCPPT_TEXT(", ")
			<< fcppt::from_std_string(resource_group.c_str())
			<< FCPPT_TEXT(")"));
	FCPPT_ASSERT_MESSAGE(
		false,
		FCPPT_TEXT("resource_provider::getResourceGroupFilenames not implemented yet!"));
	return 0;
}

fcppt::filesystem::path const
sge::cegui::resource_provider::to_absolute_path(
	CEGUI::String const &filename, 
	CEGUI::String const &)
{
	return 
		prefix_ 
			/ fcppt::from_std_string(filename.c_str());
}

sge::cegui::resource_provider::~resource_provider()
{
}
