/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/dim_type.hpp>
#include <sge/renderer/texture_pos_type.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/image.hpp>
#include <sge/renderer/subimage_view.hpp>
#include <sge/renderer/make_const_image_view.hpp>
#include <sge/renderer/fill_pixels.hpp>
#include <sge/renderer/copy_and_convert_pixels.hpp>
#include <sge/renderer/colors.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/object.hpp>
#include <sge/mainloop/catch_block.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/filesystem/directory_iterator.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/cerr.hpp>
#include <sge/iconv.hpp>
#include <boost/foreach.hpp>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cstdlib>

namespace
{

sge::renderer::size_type
calc_size(
	sge::renderer::size_type const image_count,
	sge::renderer::dim_type const &dim)
{
	for(sge::renderer::size_type i = 0; i <= 10; ++i)
	{
		sge::renderer::size_type const sz(
			1 << i
		);
		
		if((sz / (dim.w() + 1)) * (sz / (dim.h() + 1)) > image_count)
			return sz;
	}
	throw sge::exception(
		SGE_TEXT("size too big!")
	);
}

sge::renderer::dim_type const
first_dim(
	sge::filesystem::path const &p,
	sge::image::loader_ptr const il)
{
	sge::filesystem::directory_iterator const it(
		p
	);
	
	return il->load(*it)->dim();
}

typedef std::vector<
	sge::filesystem::path
> path_vector;

path_vector const
sort_paths(
	boost::filesystem::path const &p)
{
	path_vector ret;
	for(
		boost::filesystem::directory_iterator it(p);
		it != boost::filesystem::directory_iterator();
		++it
	)
		ret.push_back(*it);
	
	std::sort(
		ret.begin(),
		ret.end()
	);

	return ret;
}

}

int main(int argc, char **argv)
try
{
	if(argc != 2)
	{
		sge::cerr << SGE_TEXT("please specify a path!\n");
		return EXIT_FAILURE;
	}
	
	sge::systems::instance const sys(
		sge::systems::list
		(sge::systems::parameterless::image)
	);

	sge::image::loader_ptr const il(
		sys.image_loader()
	);

	sge::filesystem::path const path(
		sge::iconv(
			argv[1]
		)
	);

	sge::renderer::size_type const image_count(
		std::distance(
			sge::filesystem::directory_iterator(
				path
			),
			sge::filesystem::directory_iterator()
		)
	);

	if(image_count == 0)
	{
		sge::cerr << SGE_TEXT("No files here.\n");
		return EXIT_SUCCESS;
	}

	sge::renderer::dim_type const dim(
		first_dim(
			path,
			il
		)
	);
	
	sge::renderer::size_type const border_sz(
		calc_size(
			image_count,
			dim
		)
	);

	sge::renderer::rgba8_image dest(
		border_sz,
		border_sz
	);

	sge::renderer::image_view const dest_view(
		boost::gil::view(
			dest
		)
	);

	sge::renderer::fill_pixels(
		dest_view,
		sge::renderer::colors::transparent()
	);

	sge::renderer::texture_pos_type pos(
		sge::renderer::texture_pos_type::null()
	);

	path_vector const paths(
		sort_paths(
			path
		)
	);
	BOOST_FOREACH(
		path_vector::const_reference path,
		paths
	)
	{
		sge::image::object_ptr const img(
			il->load(
				path
			)
		);

		if(img->dim() != dim)
		{
			sge::cerr << SGE_TEXT("some dimensions do not match!\n");
			return EXIT_FAILURE;
		}

		sge::renderer::copy_and_convert_pixels(
			img->view(),
			sge::renderer::subimage_view(
				dest_view,
				sge::renderer::lock_rect(
					pos,
					dim
				)
			)
		);

		pos.x() += dim.w() + 1;
		if(pos.x() + dim.w() + 1 > border_sz)
		{
			pos.x() = 0;
			pos.y() += dim.h() + 1;
		}
	}

	il->create(
		sge::renderer::make_const_image_view(
			dest_view
		)
	)->save(
		SGE_TEXT("out.png")
	);
}
SGE_MAINLOOP_CATCH_BLOCK
