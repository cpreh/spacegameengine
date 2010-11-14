#ifndef SGE_SHADER_VECTOR_TO_STRING_HPP_INCLUDED
#define SGE_SHADER_VECTOR_TO_STRING_HPP_INCLUDED

#include <sge/renderer/vf/vertex_size.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <fcppt/lexical_cast.hpp>

namespace sge
{
namespace shader
{
template<typename T,renderer::vf::vertex_size N>
renderer::glsl::string const
vector_to_string()
{
	return "vec"+fcppt::lexical_cast<renderer::glsl::string>(N);
}
}
}

#endif
