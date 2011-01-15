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


#include <sge/shader/sampler.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/texture_base.hpp>
#include <sge/renderer/texture_base_ptr.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/texture_ptr.hpp>
#include <sge/renderer/volume_texture_ptr.hpp>
#include <sge/renderer/volume_texture.hpp>
#include <sge/renderer/cube_texture_ptr.hpp>
#include <sge/renderer/cube_texture.hpp>
#include <sge/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/apply_binary.hpp>
#include <fcppt/type_name.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <typeinfo>
#include <limits>

namespace
{
struct to_base_ptr
{
	typedef
	sge::renderer::texture_base_ptr
	result_type;

	template<typename T>
	result_type const
	operator()(
		T const &t) const
	{
		return t;
	}
};

struct test_assign
{
public:
	typedef
	void
	result_type;

	template<typename T,typename U>
	typename
	boost::disable_if_c
	<
		boost::is_same<T,U>::value,
		result_type
	>::type
	operator()(
		T const &,U const &) const
	{
		throw 
			sge::exception(
				FCPPT_TEXT("Texture type mismatch, tried to assign a ")+
				fcppt::type_name(
					typeid(U))+
				FCPPT_TEXT(" to a texture of type ")+
				fcppt::type_name(
					typeid(T)));
	}

	template<typename T,typename U>
	typename
	boost::enable_if_c
	<
		boost::is_same<T,U>::value,
		result_type
	>::type
	operator()(
		T const &,U const &) const
	{
	}
};

struct texture_to_sampler
{
public:
	typedef
	sge::renderer::glsl::string
	result_type;

	result_type const
	operator()(
		sge::renderer::texture_ptr const &) const
	{
		return "sampler2D";
	}

	result_type const
	operator()(
		sge::renderer::volume_texture_ptr const &) const
	{
		return "sampler3D";
	}

	result_type const
	operator()(
		sge::renderer::cube_texture_ptr const &) const
	{
		return "samplerCube";
	}
};
}

sge::shader::sampler::sampler(
	sge::renderer::glsl::string const &_name,
	texture_variant const &_texture)
:
	name_(
		_name),
	declaration_(
		"uniform "+
		fcppt::variant::apply_unary(
			texture_to_sampler(),
			_texture)+
		" "+
		_name+
		";"),
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
	return 
		fcppt::variant::apply_unary(
			to_base_ptr(),
			texture_);
}

void
sge::shader::sampler::texture(
	texture_variant const &_texture)
{
	fcppt::variant::apply_binary(
		test_assign(),
		texture_,
		_texture);
	texture_ = _texture;
}

sge::shader::sampler::~sampler()
{
}
