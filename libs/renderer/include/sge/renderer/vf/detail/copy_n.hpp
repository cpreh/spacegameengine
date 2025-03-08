//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VF_DETAIL_COPY_N_HPP_INCLUDED
#define SGE_RENDERER_VF_DETAIL_COPY_N_HPP_INCLUDED

#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage_in_libc_call.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstring>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::vf::detail
{

inline void copy_n(
    sge::renderer::const_raw_pointer const _src,
    sge::renderer::vf::vertex_size const _sz,
    sge::renderer::raw_pointer const _dest)
{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE_IN_LIBC_CALL
  std::memcpy(_dest, _src, _sz);
FCPPT_PP_POP_WARNING
}

}

#endif
