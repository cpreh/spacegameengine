#ifndef SGE_SHADER_TEXTURE_DIMENSION_STRING_HPP_INCLUDED
#define SGE_SHADER_TEXTURE_DIMENSION_STRING_HPP_INCLUDED

#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/texture_base_fwd.hpp>

namespace sge
{
namespace shader
{
sge::renderer::glsl::string const
texture_dimension_string(
	sge::renderer::texture_base const &);
}
}

#endif
