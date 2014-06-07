/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/image2d/file.hpp>
#include <sge/image2d/load_exn.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/texture/create_planar_from_file.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>



sge::renderer::texture::planar_unique_ptr
sge::renderer::texture::create_planar_from_path(
	boost::filesystem::path const &_file,
	sge::renderer::device::core &_renderer,
	sge::image2d::system &_system,
	sge::renderer::texture::mipmap::object const &_mipmap,
	sge::renderer::resource_flags_field const &_flags,
	sge::renderer::texture::emulate_srgb const _emulate_srgb
)
{
	return
		sge::renderer::texture::create_planar_from_file(
			_renderer,
			*sge::image2d::load_exn(
				_system,
				_file
			),
			_mipmap,
			_flags,
			_emulate_srgb
		);
}
