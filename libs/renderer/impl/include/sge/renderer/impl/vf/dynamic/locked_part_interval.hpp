//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_IMPL_VF_DYNAMIC_LOCKED_PART_INTERVAL_HPP_INCLUDED
#define SGE_RENDERER_IMPL_VF_DYNAMIC_LOCKED_PART_INTERVAL_HPP_INCLUDED

#include <sge/renderer/impl/vf/dynamic/lock_interval.hpp>
#include <sge/renderer/vf/dynamic/locked_part_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace impl
{
namespace vf
{
namespace dynamic
{

sge::renderer::impl::vf::dynamic::lock_interval
locked_part_interval(
	sge::renderer::vf::dynamic::locked_part const &
);

}
}
}
}
}

#endif
