//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_KEY_CODE_TO_DIGIT_HPP_INCLUDED
#define SGE_INPUT_KEY_CODE_TO_DIGIT_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/key/code_fwd.hpp>
#include <sge/input/key/optional_digit_fwd.hpp>


namespace sge
{
namespace input
{
namespace key
{

SGE_INPUT_DETAIL_SYMBOL
sge::input::key::optional_digit
code_to_digit(
	sge::input::key::code
);

}
}
}

#endif
