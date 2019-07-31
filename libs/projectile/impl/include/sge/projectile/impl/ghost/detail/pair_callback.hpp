//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_IMPL_GHOST_DETAIL_PAIR_CALLBACK_HPP_INCLUDED
#define SGE_PROJECTILE_IMPL_GHOST_DETAIL_PAIR_CALLBACK_HPP_INCLUDED

// The header below isn't self-contained, this is a fix for that
struct btBroadphaseProxy;

#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <BulletCollision/BroadphaseCollision/btOverlappingPairCallback.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace projectile
{
namespace ghost
{
namespace detail
{

class pair_callback
:
	public btOverlappingPairCallback
{
	FCPPT_NONCOPYABLE(
		pair_callback
	);
public:
	pair_callback();

	~pair_callback()
	override;
private:
	btBroadphasePair *
	addOverlappingPair(
		btBroadphaseProxy*,
		btBroadphaseProxy*
	)
	override;

	void *
	removeOverlappingPair(
		btBroadphaseProxy*,
		btBroadphaseProxy*,
		btDispatcher*
	)
	override;

	void
	removeOverlappingPairsContainingProxy(
		btBroadphaseProxy*,
		btDispatcher*
	)
	override;
};

}
}
}
}

#endif
