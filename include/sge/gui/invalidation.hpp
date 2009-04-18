#ifndef SGE_GUI_INVALIDATION_HPP_INCLUDED
#define SGE_GUI_INVALIDATION_HPP_INCLUDED

#include <sge/bitfield.hpp>
// hrhr, no impl crap for me!
#include <sge/bitfield_impl.hpp>

namespace sge
{
namespace gui
{
namespace invalidation
{
enum internal_type
{
	position,
	size,
	enum_size
};

typedef bitfield<internal_type,enum_size> type;

extern type const all;
}
}
}

#endif
