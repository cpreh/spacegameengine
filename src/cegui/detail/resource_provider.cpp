#include "../declare_local_logger.hpp"
#include <sge/cegui/detail/resource_provider.hpp>
#include <sge/cegui/exception.hpp>
#include <sge/cegui/from_cegui_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert_message.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fstream>
#include <iostream>
#include <ios>
#include <cstddef>

SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("resource_provider"))

sge::cegui::detail::resource_provider::resource_provider(
	fcppt::filesystem::path const &_prefix,
	sge::charconv::system_ptr const _charconv_system)
:
	prefix_(
		_prefix),
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

//	std::cerr << "from_cegui_string: " << filename.c_str() << " (length " << filename.length() << ")\n";
	fcppt::string const converted = 
		from_cegui_string(
			filename,
			charconv_system_);
//	std::cerr << "from_cegui_string end\n";

	// The problem here is that the resource provider is used for
	// "internally linked files" such as the imagesets as well as
	// "externally loaded" files like the layout files. So we first try
	// to load it with a prefix and then without. Not perfect, but it
	// suffices for now.
	fcppt::scoped_ptr<fcppt::io::cifstream> file_stream(
		new fcppt::io::cifstream(
			prefix_ / converted));

	if(!file_stream->is_open())
	{
		file_stream.reset(
			new fcppt::io::cifstream(
				converted));

		if(!file_stream->is_open())
			throw exception(
				FCPPT_TEXT("Coudn't open file \"")+
				converted+
				FCPPT_TEXT("\""));
	}

	file_stream->seekg(
		0,
		std::ios_base::end);

	std::streampos const filesize = 
		file_stream->tellg();

	CEGUI::uint8 *data = new CEGUI::uint8[static_cast<std::size_t>(filesize)];

	file_stream->seekg(
		0,
		std::ios_base::beg);

	file_stream->read(
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
sge::cegui::detail::resource_provider::to_absolute_path(
	CEGUI::String const &filename, 
	CEGUI::String const &)
{
	return 
		prefix_ 
			/ fcppt::from_std_string(filename.c_str());
}

sge::cegui::detail::resource_provider::~resource_provider()
{
}
