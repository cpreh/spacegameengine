//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_RESOURCE_LIST_HPP_INCLUDED
#define SGE_D3D9_RESOURCE_LIST_HPP_INCLUDED

#include <sge/d3d9/resource.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/intrusive/list.hpp>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace d3d9
{

typedef boost::intrusive::list<resource, boost::intrusive::constant_time_size<false>> resource_list;

}
}

#endif
