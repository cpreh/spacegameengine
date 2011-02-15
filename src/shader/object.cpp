/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/shader/object.hpp>
#include <sge/exception.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/glsl/optional_string.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/glsl/uniform/single_value.hpp>
#include <sge/renderer/glsl/uniform/variable_ptr.hpp>
#include <sge/renderer/glsl/program.hpp>
#include <sge/renderer/glsl/no_program.hpp>
#include <sge/renderer/glsl/scoped_program.hpp>
#include <sge/renderer/no_texture.hpp>
#include <sge/log/global.hpp>
#include <fcppt/filesystem/exists.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/text.hpp>
// Minimal includes my ass
#include <fcppt/log/headers.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/range/numeric.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/operator.hpp>
#include <boost/spirit/home/phoenix/bind.hpp>
#include <streambuf>

namespace
{
// We have to convert the Shader files to a string so we can replace
// the header "macros" by the real header.
sge::renderer::glsl::string const
file_to_string(
	fcppt::filesystem::path const &p)
{
	fcppt::io::cifstream stream(
		p);
	return 
		sge::renderer::glsl::string(
			std::istreambuf_iterator<sge::renderer::glsl::string::value_type>(
				stream),
			std::istreambuf_iterator<sge::renderer::glsl::string::value_type>());
}

// TODO: Replace by some lambda?
struct uniform_setter
{
public:
	// apply_unary needs this 
	typedef void result_type;

	sge::renderer::glsl::uniform::variable_ptr variable_;

	explicit
	uniform_setter(
		sge::renderer::glsl::uniform::variable_ptr const _variable)
	:
		variable_(_variable)
	{
	}

	template<typename T>
	result_type
	operator()(T const &_value) const
	{
		sge::renderer::glsl::uniform::single_value(
			variable_,
			_value);
	}
};
}

sge::shader::object::object(
	renderer::device_ptr const _renderer,
	fcppt::filesystem::path const &vertex,
	fcppt::filesystem::path const &fragment,
	renderer::glsl::string const &format_declaration,
	variable_sequence const &_variables,
	sampler_sequence const &_samplers)
:
	renderer_(
		_renderer)
{
	if (!fcppt::filesystem::exists(vertex))
		throw exception(
			FCPPT_TEXT("Vertex shader file\n")+
			fcppt::filesystem::path_to_string(
				vertex
			)
			+
			FCPPT_TEXT("\ndoes not exist!"));
	
	if (!fcppt::filesystem::exists(fragment))
		throw exception(
			FCPPT_TEXT("Fragment shader file\n")+
			fcppt::filesystem::path_to_string(
				fragment
			)
			+
			FCPPT_TEXT("\ndoes not exist!"));

	renderer::glsl::string const header = 
		boost::accumulate(
			_variables,
			sge::renderer::glsl::string(),
			boost::phoenix::arg_names::arg1 + 
				boost::phoenix::bind(
					&variable::declaration,
					boost::phoenix::arg_names::arg2)) +
		boost::accumulate(
			_samplers,
			sge::renderer::glsl::string(),
			boost::phoenix::arg_names::arg1 + 
				boost::phoenix::bind(
					&sampler::declaration,
					boost::phoenix::arg_names::arg2));

	program_ = 
		renderer_->create_glsl_program(
			sge::renderer::glsl::optional_string(
				boost::algorithm::replace_first_copy(
					::file_to_string(
						vertex),
					std::string("$$$HEADER$$$"),
					format_declaration
					+ header)),
			sge::renderer::glsl::optional_string(
				boost::algorithm::replace_first_copy(
					::file_to_string(
						fragment),
					std::string("$$$HEADER$$$"),
					header)));

	sge::renderer::glsl::scoped_program scoped_shader_(
		renderer_,
		program_);

	BOOST_FOREACH(variable const &v,_variables)
	{
		if (v.type() != variable_type::uniform)
			continue;

		uniforms_.insert(
			uniform_map::value_type(
				v.name(),
					program_->uniform(v.name())));

		set_uniform(
			v.name(),
			v.initial_value());
		// TODO: See above
		/*
		fcppt::variant::apply_unary(
			uniform_setter(
				uniforms_.insert(
					uniform_map::value_type(
						v.name(),
						program_->uniform(v.name()))).first->second),
			v.initial_value());
		*/
	}

	sampler::texture_unit_type current_tu = 
		static_cast<sampler::texture_unit_type>(0);
	BOOST_FOREACH(
		sampler const &v,
		_samplers)
	{
		samplers_.push_back(
			v);

		sge::renderer::glsl::uniform::single_value(
			uniforms_.insert(
				uniform_map::value_type(
					v.name(),
					program_->uniform(v.name()))).first->second,
			current_tu);

		samplers_.back().texture_unit(
			current_tu);

		++current_tu;
	}
	
	if (!program_->info_log().empty())
	{
		FCPPT_LOG_INFO(
			log::global(),
			fcppt::log::_ 
				<< FCPPT_TEXT("Shader program error log: ")
				<< program_->info_log()
				<< FCPPT_TEXT("\n"));
	}
}

void
sge::shader::object::set_uniform(
	sge::renderer::glsl::string const &name,
	value_type const &v)
{
	uniform_map::iterator const i = 
		uniforms_.find(name);

	if (i == uniforms_.end())
		throw exception(
			FCPPT_TEXT("Uniform ")+
			fcppt::from_std_string(
				name)+
			FCPPT_TEXT(" was not found"));

	fcppt::variant::apply_unary(
		uniform_setter(
			i->second),
		v);
}

void
sge::shader::object::update_texture(
	sge::renderer::glsl::string const &name,
	texture_variant const &newtex)
{
	BOOST_FOREACH(
		sampler_sequence::reference r,
		samplers_)
	{
		if (r.name() == name)
		{
			r.texture(
				newtex);
			return;
		}
	}

	throw 
		sge::exception(
			FCPPT_TEXT("The texture \"")+
			fcppt::from_std_string(name)+
			FCPPT_TEXT("\" you tried to update in a shader doesn't exist!"));
}

sge::renderer::glsl::program_ptr const
sge::shader::object::program()
{
	return program_;
}

void
sge::shader::object::activate()
{
	renderer_->glsl_program(
		program_);
	
	BOOST_FOREACH(
		sampler_sequence::const_reference r,
		samplers_)
		renderer_->texture(
			r.texture(),
			static_cast<
				sge::renderer::stage_type
			>(
				r.texture_unit()));
}

void
sge::shader::object::deactivate()
{
	renderer_->glsl_program(
		sge::renderer::glsl::no_program());
	BOOST_FOREACH(
		sampler_sequence::const_reference r,
		samplers_)
		renderer_->texture(
			sge::renderer::no_texture(),
			static_cast<
				sge::renderer::stage_type
			>(
				r.texture_unit()));
}

sge::shader::object::~object()
{
}
