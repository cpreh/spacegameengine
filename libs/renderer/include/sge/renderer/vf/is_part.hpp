//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_IS_PART_HPP_INCLUDED
#define SGE_RENDERER_VF_IS_PART_HPP_INCLUDED

#include <sge/renderer/vf/part_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{

template<
	typename Type
>
struct is_part
:
std::false_type
{
};

template<
	typename... Elements
>
struct is_part<
	sge::renderer::vf::part<
		Elements...
	>
>
:
std::true_type
{
};

}
}
}

#endif
