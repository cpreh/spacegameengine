//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_POSTPROCESSING_VF_FORMAT_PART_HPP_INCLUDED
#define SGE_POSTPROCESSING_VF_FORMAT_PART_HPP_INCLUDED

#include <sge/postprocessing/vf/position.hpp>
#include <sge/postprocessing/vf/texcoord.hpp>
#include <sge/renderer/vf/part.hpp>


namespace sge
{
namespace postprocessing
{
namespace vf
{

typedef
sge::renderer::vf::part<
	sge::postprocessing::vf::position,
	sge::postprocessing::vf::texcoord
>
format_part;

}
}
}

#endif
