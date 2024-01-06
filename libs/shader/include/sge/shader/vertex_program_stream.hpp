//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SHADER_VERTEX_PROGRAM_STREAM_HPP_INCLUDED
#define SGE_SHADER_VERTEX_PROGRAM_STREAM_HPP_INCLUDED

#include <sge/shader/istream_ref.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sge::shader
{

FCPPT_DECLARE_STRONG_TYPEDEF(sge::shader::istream_ref, vertex_program_stream);

}

#endif
