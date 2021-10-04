//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_FOCUS_KEY_HPP_INCLUDED
#define SGE_INPUT_FOCUS_KEY_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/focus/key_fwd.hpp>
#include <sge/input/key/code.hpp>


namespace sge::input::focus
{

class key
{
public:
	SGE_INPUT_DETAIL_SYMBOL
	explicit
	key(
		sge::input::key::code
	);

	[[nodiscard]]
	SGE_INPUT_DETAIL_SYMBOL
	sge::input::key::code
	code() const;
private:
	sge::input::key::code code_;
};

SGE_INPUT_DETAIL_SYMBOL
bool
operator==(
	sge::input::focus::key const &,
	sge::input::focus::key const &
);

SGE_INPUT_DETAIL_SYMBOL
bool
operator!=(
	sge::input::focus::key const &,
	sge::input::focus::key const &
);

}

#endif
