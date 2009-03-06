#ifndef SGE_COLLISION_SYSTEM_HPP_INCLUDED
#define SGE_COLLISION_SYSTEM_HPP_INCLUDED

#include <sge/collision/world_fwd.hpp>
#include <sge/collision/optional_rect.hpp>
#include <sge/export.hpp>
#include <boost/optional.hpp>
#include <boost/noncopyable.hpp>

namespace sge
{
namespace collision
{
class SGE_CLASS_SYMBOL system : boost::noncopyable
{
public:
	virtual world_ptr const create_world(
		optional_rect const & = boost::none) = 0;
	virtual ~system();
};
}
}

#endif
