#include <sge/cegui/from_cegui_string.hpp>
#include <CEGUI/CEGUIBase.h>
#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/charconv/string_type.hpp>
#include <fcppt/from_std_wstring.hpp>
#include <boost/static_assert.hpp>
#include <iostream>

fcppt::string const
sge::cegui::from_cegui_string(
	CEGUI::String const &s,
	sge::charconv::system_ptr const charconv)
{
	typedef
	sge::charconv::string_type<sge::charconv::encoding::utf32>::type
	source_string;

	BOOST_STATIC_ASSERT((
		boost::is_same
		<
			source_string::value_type,
			CEGUI::utf32
		>::value));

	typedef
	sge::charconv::string_type<sge::charconv::encoding::wchar>::type
	dest_string;

	dest_string d = 
		sge::charconv::convert
			<
				sge::charconv::encoding::wchar, 
				sge::charconv::encoding::utf32
			>(
				charconv,
				source_string(
					s.begin(),
					s.end()));

	return s.c_str();
	return fcppt::from_std_wstring(d);
	/*
	dest_string d = 

	return 
		fcppt::from_std_wstring(
			sge::charconv::convert
			<
				sge::charconv::encoding::wchar, 
				sge::charconv::encoding::utf32
			>(
				charconv,
				source_string(
					s.begin(),
					s.end())));
	*/
}
