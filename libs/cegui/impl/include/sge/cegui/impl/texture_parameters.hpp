/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_CEGUI_IMPL_TEXTURE_PARAMETERS_HPP_INCLUDED
#define SGE_CEGUI_IMPL_TEXTURE_PARAMETERS_HPP_INCLUDED

#include <sge/cegui/impl/prefix.hpp>
#include <sge/cegui/impl/texture_parameters_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge
{
namespace cegui
{
namespace impl
{

class texture_parameters
{
public:
	texture_parameters(
		sge::cegui::impl::prefix const &,
		sge::image2d::system &,
		sge::renderer::device::ffp &,
		sge::renderer::texture::emulate_srgb
	);

	sge::cegui::impl::prefix const &
	prefix() const;

	sge::image2d::system &
	image_system() const;

	sge::renderer::device::ffp &
	renderer() const;

	sge::renderer::texture::emulate_srgb
	emulate_srgb() const;
private:
	sge::cegui::impl::prefix prefix_;

	fcppt::reference<
		sge::image2d::system
	> image_system_;

	fcppt::reference<
		sge::renderer::device::ffp
	> renderer_;

	sge::renderer::texture::emulate_srgb emulate_srgb_;
};

}
}
}

#endif
