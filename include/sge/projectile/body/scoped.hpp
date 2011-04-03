#ifndef SGE_PROJECTILE_BODY_SCOPED_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_SCOPED_HPP_INCLUDED

#include <sge/projectile/symbol.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/body/object_fwd.hpp>
#include <sge/projectile/group/sequence.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace projectile
{
namespace body
{
class scoped
{
FCPPT_NONCOPYABLE(
	scoped);
public:
	SGE_PROJECTILE_SYMBOL explicit
	scoped(
		world &,
		object &,
		group::sequence const &);

	SGE_PROJECTILE_SYMBOL ~scoped();
private:
	world &world_;
	object &object_;
};
}
}
}

#endif
