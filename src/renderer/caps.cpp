/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/caps.hpp>
#include <sge/image/color/format_to_string.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/text.hpp>
#include <ostream>

sge::renderer::caps::caps(
	adapter_type const adapter_,
	fcppt::string const &driver_name_,
	fcppt::string const &description_,
	dim2 const &max_texture_size_,
	filter::anisotropy_type const max_anisotropy_,
	bool const render_target_supported_,
	bool const glsl_supported_,
	image::color::format::type const preferred_texture_format_
)
:
	adapter_(adapter_),
	driver_name_(driver_name_),
	description_(description_),
	max_texture_size_(max_texture_size_),
	max_anisotropy_(max_anisotropy_),
	render_target_supported_(render_target_supported_),
	glsl_supported_(glsl_supported_),
	preferred_texture_format_(preferred_texture_format_)
{}

sge::renderer::adapter_type
sge::renderer::caps::adapter() const
{
	return adapter_;
}

fcppt::string const &
sge::renderer::caps::driver_name() const
{
	return driver_name_;
}

fcppt::string const &
sge::renderer::caps::description() const
{
	return description_;
}

sge::renderer::dim2 const &
sge::renderer::caps::max_texture_size() const
{
	return max_texture_size_;
}

sge::renderer::filter::anisotropy_type
sge::renderer::caps::max_anisotropy() const
{
	return max_anisotropy_;
}

bool
sge::renderer::caps::render_target_supported() const
{
	return render_target_supported_;
}

bool
sge::renderer::caps::glsl_supported() const
{
	return glsl_supported_;
}


sge::image::color::format::type
sge::renderer::caps::preferred_texture_format() const
{
	return preferred_texture_format_;
}

fcppt::io::ostream &
sge::renderer::operator<<(
	fcppt::io::ostream &_stream,
	caps const &_caps
)
{
	return _stream
		<< FCPPT_TEXT("caps: adapter = ")
		<< _caps.adapter()
		<< FCPPT_TEXT(", driver_name = \"")
		<< _caps.driver_name()
		<< FCPPT_TEXT("\", description = \"")
		<< _caps.description()
		<< FCPPT_TEXT("\", max_texture_size = ")
		<< _caps.max_texture_size()
		<< FCPPT_TEXT(", max_anisotropy = ")
		<< _caps.max_anisotropy()
		<< FCPPT_TEXT(", glsl_supported = ")
		<< std::boolalpha
		<< _caps.glsl_supported()
		<< FCPPT_TEXT(", preferred_texture_format = ")
		<< sge::image::color::format_to_string(
			_caps.preferred_texture_format()
		);
}
