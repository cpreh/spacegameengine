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


#ifndef SGE_SCENIC_TEXTURE_MANAGER_HPP_INCLUDED
#define SGE_SCENIC_TEXTURE_MANAGER_HPP_INCLUDED

#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/scenic/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace scenic
{
class texture_manager
{
FCPPT_NONCOPYABLE(
	texture_manager);
public:
	SGE_SCENIC_SYMBOL
	texture_manager(
		sge::renderer::device::core &,
		sge::image2d::system &);

	SGE_SCENIC_SYMBOL
	sge::renderer::texture::planar &
	texture_for_path(
		boost::filesystem::path const &);

	SGE_SCENIC_SYMBOL
	~texture_manager();
private:
	typedef
	boost::ptr_map
	<
		boost::filesystem::path,
		sge::renderer::texture::planar
	>
	path_to_texture_map;

	sge::renderer::device::core &renderer_;
	sge::image2d::system &image_loader_;
	path_to_texture_map path_to_texture_;
};
}
}

#endif
