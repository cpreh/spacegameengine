//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TEXTURE_PART_RAW_REF_HPP_INCLUDED
#define SGE_TEXTURE_PART_RAW_REF_HPP_INCLUDED

#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/texture/part_raw_ref_fwd.hpp>
#include <sge/texture/detail/declare_basic_part_raw.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SGE_TEXTURE_DETAIL_DECLARE_BASIC_PART_RAW(
	sge::renderer::texture::planar &
);

FCPPT_PP_POP_WARNING

#endif
