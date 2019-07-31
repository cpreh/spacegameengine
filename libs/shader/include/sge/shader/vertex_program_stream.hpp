//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SHADER_VERTEX_PROGRAM_STREAM_HPP_INCLUDED
#define SGE_SHADER_VERTEX_PROGRAM_STREAM_HPP_INCLUDED

#include <sge/shader/istream_ref.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace shader
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sge::shader::istream_ref,
	vertex_program_stream
);

}
}

#endif
