//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_RENDER_CONTEXT_TRANSFORM_MATRIX_TYPE_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_TRANSFORM_MATRIX_TYPE_HPP_INCLUDED

#include <sge/scenic/render_context/transform_matrix_type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::scenic::render_context
{

enum class transform_matrix_type : std::uint8_t
{
  projection,
  world
};

}

#endif
