#include <sge/shader/sampler.hpp>
#include <fcppt/text.hpp>
#include <limits>

sge::shader::sampler::sampler(
	sge::renderer::glsl::string const &_name,
	sge::renderer::texture_base_ptr const _texture)
:
	name_(
		_name),
	declaration_(
		FCPPT_TEXT("uniform sampler2D ")+_name+FCPPT_TEXT(";")),
	texture_(
		_texture),
	texture_unit_(
		std::numeric_limits<texture_unit_type>::max())
{
}

sge::renderer::glsl::string const
sge::shader::sampler::name() const
{
	return name_;
}

sge::renderer::glsl::string const
sge::shader::sampler::declaration() const
{
	return declaration_;
}

void
sge::shader::sampler::texture_unit(
	texture_unit_type const _texture_unit)
{
	texture_unit_ = _texture_unit;
}

// This is needed on shader activation
sge::shader::sampler::texture_unit_type
sge::shader::sampler::texture_unit() const
{
	return texture_unit_;
}

// This is needed on shader activation
sge::renderer::texture_base_ptr const
sge::shader::sampler::texture() const
{
	return texture_;
}

void
sge::shader::sampler::texture(
	sge::renderer::texture_base_ptr const _texture)
{
	texture_ = _texture;
}

sge::shader::sampler::~sampler()
{
}
