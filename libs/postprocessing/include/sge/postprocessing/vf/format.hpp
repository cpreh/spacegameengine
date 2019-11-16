//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_POSTPROCESSING_VF_FORMAT_HPP_INCLUDED
#define SGE_POSTPROCESSING_VF_FORMAT_HPP_INCLUDED

#include <sge/postprocessing/vf/format_part.hpp>
#include <sge/renderer/vf/format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/list/list.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace postprocessing
{
namespace vf
{

typedef
sge::renderer::vf::format<
	metal::list<
		sge::postprocessing::vf::format_part
	>
>
format;

}
}
}

#endif
