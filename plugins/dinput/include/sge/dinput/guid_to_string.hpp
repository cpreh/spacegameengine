//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_DINPUT_GUID_TO_STRING_HPP_INCLUDED
#define SGE_DINPUT_GUID_TO_STRING_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace dinput
{

fcppt::string
guid_to_string(
	GUID const &
);

}
}

#endif
