#ifndef SGE_INPUT_MODIFIER_OBJECT_HPP_INCLUDED
#define SGE_INPUT_MODIFIER_OBJECT_HPP_INCLUDED

#include "types.hpp"
#include <sge/input/key_code.hpp>
#include <vector>

namespace sge
{
namespace input
{
namespace modifier
{
struct object
{
	typedef std::vector<sge::input::key_code> code_container;

	code_container codes;
	sge::input::modifier::types::type t;

	object(code_container const &codes,types::type const t)
		: codes(codes),t(t) {}
};
}
}
}

#endif
