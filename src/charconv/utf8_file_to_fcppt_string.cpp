#include <sge/charconv/utf8_file_to_fcppt_string.hpp>
#include <sge/charconv/exception.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <iterator>
#include <string>
#include <fcppt/config/external_end.hpp>


fcppt::string const
sge::charconv::utf8_file_to_fcppt_string(
	sge::charconv::system &charconv_system,
	boost::filesystem::path const &path)
{
	boost::filesystem::ifstream file_stream(
		path);

	if(!file_stream.is_open())
		throw
			sge::charconv::exception(
				FCPPT_TEXT("Couldn't open file \"")+
				fcppt::filesystem::path_to_string(
					path));

	return
		sge::charconv::utf8_string_to_fcppt(
			charconv_system,
			sge::charconv::utf8_string(
				std::istreambuf_iterator<char>(
					file_stream),
				std::istreambuf_iterator<char>()));
}
