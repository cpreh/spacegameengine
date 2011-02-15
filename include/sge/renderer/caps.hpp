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


#ifndef SGE_RENDERER_CAPS_HPP_INCLUDED
#define SGE_RENDERER_CAPS_HPP_INCLUDED

#include <sge/renderer/caps_fwd.hpp>
#include <sge/renderer/adapter_type.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/texture/filter/anisotropy_type.hpp>
#include <sge/image/color/format.hpp>
#include <sge/symbol.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/string.hpp>

namespace sge
{
namespace renderer
{

class caps
{
public:
	SGE_SYMBOL caps(
		adapter_type adapter_,
		fcppt::string const &driver_name,
		fcppt::string const &description,
		dim2 const &max_texure_size,
		texture::filter::anisotropy_type max_anisotropy_,
		bool render_target_supported,
		bool glsl_supported,
		image::color::format::type preferred_texture_format
	);

	SGE_SYMBOL adapter_type
	adapter() const;

	SGE_SYMBOL fcppt::string const &
	driver_name() const;

	SGE_SYMBOL fcppt::string const &
	description() const;

	SGE_SYMBOL dim2 const &
	max_texture_size() const;

	SGE_SYMBOL texture::filter::anisotropy_type
	max_anisotropy() const;

	SGE_SYMBOL bool
	render_target_supported() const;

	SGE_SYMBOL bool
	glsl_supported() const;

	SGE_SYMBOL image::color::format::type
	preferred_texture_format() const;
private:
	adapter_type adapter_;

	fcppt::string driver_name_;

	fcppt::string description_;

	dim2 max_texture_size_;

	texture::filter::anisotropy_type max_anisotropy_;

	bool render_target_supported_;

	bool glsl_supported_;

	image::color::format::type preferred_texture_format_;
};

SGE_SYMBOL
fcppt::io::ostream &
operator<<(
	fcppt::io::ostream &,
	caps const &
);

}
}

#endif
