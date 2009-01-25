#ifndef SGE_BULLET_CONVERSION_HPP_INCLUDED
#define SGE_BULLET_CONVERSION_HPP_INCLUDED

#include <sge/collision/point.hpp>
#include "types.hpp"

namespace sge
{
namespace bullet
{
point const sge_to_bullet(collision::point const &);
collision::point const bullet_to_sge(point const &);
}
}

#endif
