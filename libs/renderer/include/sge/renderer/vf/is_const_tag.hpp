//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VF_IS_CONST_TAG_HPP_INCLUDED
#define SGE_RENDERER_VF_IS_CONST_TAG_HPP_INCLUDED

#include <sge/renderer/vf/const_tag.hpp>
#include <sge/renderer/vf/nonconst_tag.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::vf
{

template <typename Type>
struct is_const_tag : std::false_type
{
};

template <>
struct is_const_tag<sge::renderer::vf::const_tag> : std::true_type
{
};

template <>
struct is_const_tag<sge::renderer::vf::nonconst_tag> : std::true_type
{
};

}

#endif
