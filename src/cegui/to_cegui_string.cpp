#include <sge/cegui/to_cegui_string.hpp>
#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <fcppt/to_std_wstring.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>
#include <string>

CEGUI::String const
sge::cegui::to_cegui_string(
	fcppt::string const &s,
	sge::charconv::system_ptr const charconv)
{
	typedef
	sge::charconv::string_type<sge::charconv::encoding::utf8>::type
	utf8_string;

	BOOST_STATIC_ASSERT((
		boost::is_same
		<
			utf8_string::value_type,
			CEGUI::utf8
		>::value));

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
