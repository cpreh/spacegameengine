//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TEXTURE_VOLUME_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_VOLUME_HPP_INCLUDED

#include <sge/image3d/tag.hpp>
#include <sge/image3d/traits/dimension.hpp>
#include <sge/renderer/texture/volume_fwd.hpp>
#include <sge/renderer/texture/detail/declare_basic_lockable_box.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SGE_RENDERER_TEXTURE_DETAIL_DECLARE_BASIC_LOCKABLE_BOX(
	sge::image3d::tag
);

FCPPT_PP_POP_WARNING

#endif
