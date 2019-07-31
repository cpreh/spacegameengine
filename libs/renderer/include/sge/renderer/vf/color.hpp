//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_COLOR_HPP_INCLUDED
#define SGE_RENDERER_VF_COLOR_HPP_INCLUDED

#include <sge/renderer/vf/color_base.hpp>
#include <sge/renderer/vf/color_fwd.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Format
>
struct color
:
sge::renderer::vf::color_base<
	Format
>
{
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
