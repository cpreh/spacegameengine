#ifndef SGE_COLLISION_BODY_HPP_INCLUDED
#define SGE_COLLISION_BODY_HPP_INCLUDED

#include <sge/collision/shapes/base_fwd.hpp>
#include <sge/collision/body_fwd.hpp>
#include <sge/collision/point.hpp>
#include <sge/noncopyable.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace collision
{
class SGE_CLASS_SYMBOL body
{
	SGE_NONCOPYABLE(body)
protected:
	SGE_SYMBOL body();
public:
	virtual point const position() const = 0;
	virtual void position(
		point const &) = 0;
	virtual point const linear_velocity() const = 0;
	virtual void linear_velocity(
		point const &) = 0;
	virtual void add(
		shapes::base_ptr) = 0;
	virtual bool is_active() = 0;
	virtual void is_active(
		bool) = 0;
	SGE_SYMBOL virtual ~body();
};
}
}

#endif
