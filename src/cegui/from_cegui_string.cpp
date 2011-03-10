#include <sge/cegui/from_cegui_string.hpp>
#include <CEGUI/CEGUIBase.h>
#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/charconv/string_type.hpp>
#include <fcppt/from_std_wstring.hpp>
#include <boost/static_assert.hpp>

fcppt::string const
sge::cegui::from_cegui_string(
	CEGUI::String const &s,
	sge::charconv::system_ptr const charconv)
{
	BOOST_STATIC_ASSERT((
		boost::is_same
		<
			sge::charconv::string_type<sge::charconv::encoding::utf8>::type::value_type,
			CEGUI::utf8
		>::value));
	return 
		fcppt::from_std_wstring(
			sge::charconv::convert
			<
				sge::charconv::encoding::wchar, 
				sge::charconv::encoding::utf8
			>(
				charconv,
				s.data()));
}
