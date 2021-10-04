//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_DS_CHANNEL_STENCIL_HPP_INCLUDED
#define SGE_IMAGE_DS_CHANNEL_STENCIL_HPP_INCLUDED

#include <sge/image/ds/channel/stencil_fwd.hpp>
#include <mizuiro/color/channel/tag.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge::image::ds::channel
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

struct stencil
:
mizuiro::color::channel::tag<
	stencil
>
{
};

FCPPT_PP_POP_WARNING

}

#endif
