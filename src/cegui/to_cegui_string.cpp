#include <sge/cegui/to_cegui_string.hpp>
#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <fcppt/to_std_wstring.hpp>
#include <string>

CEGUI::String const
sge::cegui::to_cegui_string(
	fcppt::string const &s,
	sge::charconv::system_ptr const charconv)
{
	return 
		CEGUI::String(
			sge::charconv::convert
			<
				sge::charconv::encoding::utf8, 
				sge::charconv::encoding::wchar
			>(
				charconv,
				fcppt::to_std_wstring(
					s)).c_str());
}
