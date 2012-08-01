#ifndef SGE_SCENIC_POSITION_HPP_INCLUDED
#define SGE_SCENIC_POSITION_HPP_INCLUDED

#include <sge/renderer/vector3.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sge
{
namespace scenic
{
FCPPT_MAKE_STRONG_TYPEDEF(
	sge::renderer::vector3,
	position);
}
}

#endif
