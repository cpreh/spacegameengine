//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VF_DETAIL_RAW_DATA_TYPE_HPP_INCLUDED
#define SGE_RENDERER_VF_DETAIL_RAW_DATA_TYPE_HPP_INCLUDED

#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::vf::detail
{

template <typename T>
using raw_data_type = std::
    conditional_t<std::is_const_v<T>, sge::renderer::const_raw_pointer, sge::renderer::raw_pointer>;

}

#endif
