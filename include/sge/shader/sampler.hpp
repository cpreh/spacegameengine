#ifndef SGE_SHADER_SAMPLER_HPP_INCLUDED
#define SGE_SHADER_SAMPLER_HPP_INCLUDED

#include <sge/shader/symbol.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/texture_base_ptr.hpp>

namespace sge
{
namespace shader
{
class sampler
{
public:
	typedef
	int
	texture_unit_type;

	// Initializing with an empty texture is ok
	SGE_SHADER_SYMBOL explicit
	sampler(
		renderer::glsl::string const &name,
		renderer::texture_base_ptr = 
			renderer::texture_base_ptr());

	SGE_SHADER_SYMBOL renderer::glsl::string const
	name() const;

	SGE_SHADER_SYMBOL renderer::glsl::string const
	declaration() const;

	// The shader sets this
	SGE_SHADER_SYMBOL void
	texture_unit(
		texture_unit_type);

	// This is needed on shader activation
	SGE_SHADER_SYMBOL texture_unit_type
	texture_unit() const;

	// This is needed on shader activation
	SGE_SHADER_SYMBOL renderer::texture_base_ptr const
	texture() const;

	// In insula, we need to update the reflection texture, so we need
	// this
	SGE_SHADER_SYMBOL void
	texture(
		renderer::texture_base_ptr);
	
	SGE_SHADER_SYMBOL ~sampler();
private:
	renderer::glsl::string name_,declaration_;
	renderer::texture_base_ptr texture_;
	texture_unit_type texture_unit_;
};
}
}

#endif
