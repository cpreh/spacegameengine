#ifndef SGE_SPRITE_DEFAULTS_ADDER_HPP_INCLUDED
#define SGE_SPRITE_DEFAULTS_ADDER_HPP_INCLUDED

#include <sge/sprite/defaults/fwd.hpp>
#include <sge/sprite/roles/adder.hpp>
#include <sge/sprite/intrusive/adder_base.hpp>

namespace sge
{
namespace sprite
{
template<
	typename Choices
>
struct defaults<
	Choices,
	roles::adder
>
{
	typedef intrusive::adder_base<
		Choices
	> * type;

	static type
	get()
	{
		return 0;
	}
};
}
}

#endif
