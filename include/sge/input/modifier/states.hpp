#ifndef SGE_INPUT_MODIFIER_STATES_HPP_INCLUDED
#define SGE_INPUT_MODIFIER_STATES_HPP_INCLUDED

#include <sge/container/map_fwd.hpp>
#include <sge/input/key_code.hpp>
#include <sge/input/key_state.hpp>
#include <map>

namespace sge
{
namespace input
{
namespace modifier
{
typedef sge::container::map<
	std::map,
	sge::input::key_code,
	sge::input::key_state
> states;
}
}
}

#endif
