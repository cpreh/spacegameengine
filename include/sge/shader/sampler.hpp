#ifndef SGE_SHADER_SAMPLER_HPP_INCLUDED
#define SGE_SHADER_SAMPLER_HPP_INCLUDED

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
	explicit
	sampler(
		renderer::glsl::string const &name,
		renderer::texture_base_ptr = 
			renderer::texture_base_ptr());

	renderer::glsl::string const
	name() const;

	renderer::glsl::string const
	declaration() const;

	// The shader sets this
	void
	texture_unit(
		texture_unit_type);

	// This is needed on shader activation
	texture_unit_type
	texture_unit() const;

	// This is needed on shader activation
	renderer::texture_base_ptr const
	texture() const;

	// In insula, we need to update the reflection texture, so we need
	// this
	void
	texture(
		renderer::texture_base_ptr);
	
	~sampler();
private:
	renderer::glsl::string name_,declaration_;
	renderer::texture_base_ptr texture_;
	texture_unit_type texture_unit_;
};
}
}

#endif
