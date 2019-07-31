//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_PART_CREF_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_PART_CREF_HPP_INCLUDED

#include <sge/renderer/vf/dynamic/part_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

typedef
fcppt::reference<
	sge::renderer::vf::dynamic::part const
>
part_cref;

}
}
}
}

#endif
