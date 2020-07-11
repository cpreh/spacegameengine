//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_INPUT_HPP_INCLUDED
#define SGE_SYSTEMS_INPUT_HPP_INCLUDED

#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input_fwd.hpp>
#include <sge/systems/detail/symbol.hpp>


namespace sge
{
namespace systems
{

class input
{
public:
	SGE_SYSTEMS_DETAIL_SYMBOL
	explicit
	input(
		sge::systems::cursor_option_field const &
	);

	[[nodiscard]]
	sge::systems::cursor_option_field const &
	cursor_options() const;
private:
	sge::systems::cursor_option_field cursor_options_;
};

}
}

#endif
