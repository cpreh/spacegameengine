#ifndef SGE_COLLISION_OBJECT_HPP_INCLUDED
#define SGE_COLLISION_OBJECT_HPP_INCLUDED

#include "sattelite_fwd.hpp"
#include "object_fwd.hpp"
#include "types.hpp"
#include "../export.hpp"
#include <boost/noncopyable.hpp>

namespace sge
{
namespace collision
{
class SGE_CLASS_SYMBOL object : public boost::noncopyable
{
	public:
	virtual void pos(point const &) = 0;
	virtual point const pos() const = 0;
	virtual void speed(point const &) = 0;
	virtual point const speed() const = 0;
	SGE_SYMBOL virtual ~object();
};

}
}

#endif
