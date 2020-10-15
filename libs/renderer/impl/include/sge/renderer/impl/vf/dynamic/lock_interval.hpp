//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_IMPL_VF_DYNAMIC_LOCK_INTERVAL_HPP_INCLUDED
#define SGE_RENDERER_IMPL_VF_DYNAMIC_LOCK_INTERVAL_HPP_INCLUDED

#include <sge/renderer/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/icl/interval.hpp>
#include <fcppt/config/external_end.hpp>


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

using
lock_interval
=
boost::icl::interval<
	sge::renderer::size_type
>::type;

}
}
}
}
}

#endif
