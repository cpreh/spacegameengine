#ifndef SGE_SHADER_OBJECT_PARAMETERS_HPP_INCLUDED
#define SGE_SHADER_OBJECT_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/shader/sampler_sequence.hpp>
#include <sge/shader/symbol.hpp>
#include <sge/shader/variable_sequence.hpp>
#include <sge/shader/vertex_format_string.hpp>
#include <fcppt/filesystem/path.hpp>

namespace sge
{
namespace shader
{
class object_parameters
{
FCPPT_NONASSIGNABLE(
	object_parameters);
public:
	SGE_SHADER_SYMBOL explicit
	object_parameters(
		renderer::device &,
		fcppt::filesystem::path const &vertex,
		fcppt::filesystem::path const &fragment,
		shader::vertex_format_string const &format_declaration,
		shader::variable_sequence const &variables,
		shader::sampler_sequence const &samplers);

	SGE_SHADER_SYMBOL renderer::device &
	renderer() const;

	SGE_SHADER_SYMBOL fcppt::filesystem::path const &
	vertex_file() const;

	SGE_SHADER_SYMBOL fcppt::filesystem::path const &
	fragment_file() const;

	SGE_SHADER_SYMBOL shader::vertex_format_string const &
	vertex_format_string() const;

	SGE_SHADER_SYMBOL shader::variable_sequence const &
	variables() const;

	SGE_SHADER_SYMBOL shader::sampler_sequence const &
	samplers() const;

	SGE_SHADER_SYMBOL ~object_parameters();
private:
	renderer::device &renderer_;
	fcppt::filesystem::path const vertex_file_;
	fcppt::filesystem::path const fragment_file_;
	shader::vertex_format_string const vertex_format_string_;
	shader::variable_sequence const variables_;
	shader::sampler_sequence const samplers_;
};
}
}

#endif
