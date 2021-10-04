//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_DETAIL_LOCK_INTERVAL_SET_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_DETAIL_LOCK_INTERVAL_SET_HPP_INCLUDED

#include <sge/renderer/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/icl/interval_set.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge::renderer::vf::dynamic::detail
{

using
lock_interval_set
=
boost::icl::interval_set<
	sge::renderer::size_type
>;

}

#endif
