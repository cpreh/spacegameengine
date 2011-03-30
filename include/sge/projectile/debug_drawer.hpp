#ifndef SGE_PROJECTILE_DEBUG_DRAWER_HPP_INCLUDED
#define SGE_PROJECTILE_DEBUG_DRAWER_HPP_INCLUDED

#include <sge/projectile/detail/debug_drawer_impl_fwd.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/symbol.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/matrix4.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sge
{
namespace projectile
{
/// bullet offers registering a debug drawer to draw contact points or
/// just shapes. This class implements this interface, caching all the
/// lines and drawing them at once (if you don't do that, it'll be
/// super-slow).
class debug_drawer
{
FCPPT_NONCOPYABLE(
	debug_drawer);
public:	
	SGE_PROJECTILE_SYMBOL explicit
	debug_drawer(
		world &,
		sge::renderer::device_ptr);

	// Updates the line cache
	SGE_PROJECTILE_SYMBOL void
	update();

	// Renders the lines
	SGE_PROJECTILE_SYMBOL void
	render(
		sge::renderer::matrix4 const &);

	SGE_PROJECTILE_SYMBOL void
	active(
		bool);

	SGE_PROJECTILE_SYMBOL bool
	active() const;

	SGE_PROJECTILE_SYMBOL ~debug_drawer();
private:
	fcppt::scoped_ptr<detail::debug_drawer_impl> impl_;
};
}
}

#endif
