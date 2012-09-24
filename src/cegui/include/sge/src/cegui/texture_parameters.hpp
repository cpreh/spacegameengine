/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_CEGUI_TEXTURE_PARAMETERS_HPP_INCLUDED
#define SGE_SRC_CEGUI_TEXTURE_PARAMETERS_HPP_INCLUDED

#include <sge/charconv/system_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/src/cegui/prefix.hpp>
#include <sge/src/cegui/texture_parameters_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace cegui
{

class texture_parameters
{
	FCPPT_NONASSIGNABLE(
		texture_parameters
	);
public:
	texture_parameters(
		sge::cegui::prefix const &,
		sge::charconv::system &,
		sge::image2d::system &,
		sge::renderer::device::ffp &
	);

	sge::cegui::prefix const &
	prefix() const;

	sge::charconv::system &
	charconv_system() const;

	sge::image2d::system &
	image_system() const;

	sge::renderer::device::ffp &
	renderer() const;
private:
	sge::cegui::prefix const prefix_;

	sge::charconv::system &charconv_system_;

	sge::image2d::system &image_system_;

	sge::renderer::device::ffp &renderer_;
};

}
}

#endif
