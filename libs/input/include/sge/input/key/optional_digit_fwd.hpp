//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_KEY_OPTIONAL_DIGIT_FWD_HPP_INCLUDED
#define SGE_INPUT_KEY_OPTIONAL_DIGIT_FWD_HPP_INCLUDED

#include <sge/input/key/digit.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge
{
namespace input
{
namespace key
{

typedef
fcppt::optional::object<
	sge::input::key::digit
>
optional_digit;

}
}
}

#endif
