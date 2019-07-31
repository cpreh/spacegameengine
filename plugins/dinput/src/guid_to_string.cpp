//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/di.hpp>
#include <sge/dinput/guid_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/ostringstream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


fcppt::string
sge::dinput::guid_to_string(
	GUID const &_guid
)
{
	fcppt::io::ostringstream ostr;

	ostr
		<< std::hex
		<< _guid.Data1
		<< FCPPT_TEXT('-')
		<< _guid.Data2
		<< FCPPT_TEXT('-')
		<< _guid.Data3
		<< FCPPT_TEXT('-')
		<< _guid.Data4;

	return
		ostr.str();
}
