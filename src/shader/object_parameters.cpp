#include <sge/shader/object_parameters.hpp>

sge::shader::object_parameters::object_parameters(
	renderer::device &_renderer,
	fcppt::filesystem::path const &_vertex_file,
	fcppt::filesystem::path const &_fragment_file,
	shader::vertex_format_string const &_vertex_format_string,
	shader::variable_sequence const &_variables,
	shader::sampler_sequence const &_samplers)
:
	renderer_(
		_renderer),
	vertex_file_(
		_vertex_file),
	fragment_file_(
		_fragment_file),
	vertex_format_string_(
		_vertex_format_string),
	variables_(
		_variables),
	samplers_(
		_samplers)
{
}

sge::renderer::device &
sge::shader::object_parameters::renderer() const
{
	return renderer_;
}

fcppt::filesystem::path const &
sge::shader::object_parameters::vertex_file() const
{
	return vertex_file_;
}

fcppt::filesystem::path const &
sge::shader::object_parameters::fragment_file() const
{
	return fragment_file_;
}

sge::shader::vertex_format_string const &
sge::shader::object_parameters::vertex_format_string() const
{
	return vertex_format_string_;
}

sge::shader::variable_sequence const &
sge::shader::object_parameters::variables() const
{
	return variables_;
}

sge::shader::sampler_sequence const &
sge::shader::object_parameters::samplers() const
{
	return samplers_;
}

sge::shader::object_parameters::~object_parameters()
{
}
