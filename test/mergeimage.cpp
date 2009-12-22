/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/image/loader.hpp>
#include <sge/image/file.hpp>
#include <sge/image/dim_type.hpp>
#include <sge/image/rgba8.hpp>
#include <sge/image/store.hpp>
#include <sge/image/view/sub.hpp>
#include <sge/image/view/make_const.hpp>
#include <sge/image/algorithm/fill.hpp>
#include <sge/image/algorithm/copy_and_convert.hpp>
#include <sge/image/colors.hpp>
#include <sge/mainloop/catch_block.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/filesystem/directory_iterator.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <sge/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
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

		if((sz / (dim.w() + 1)) * (sz / (dim.h() + 1)) >= image_count)
			return sz;
	}
	throw sge::exception(
		FCPPT_TEXT("size too big!")
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
	sge::filesystem::path const &p)
{
	path_vector ret;

	std::copy(
		sge::filesystem::directory_iterator(p),
		sge::filesystem::directory_iterator(),
		std::back_inserter(
			ret
		)
	);

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
		sge::cerr << FCPPT_TEXT("please specify a path!\n");
		return EXIT_FAILURE;
	}

	sge::systems::instance const sys(
		(sge::systems::list
		(sge::systems::parameterless::image))
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
		sge::cerr << FCPPT_TEXT("No files here.\n");
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

	typedef sge::image::rgba8 image_type;

	image_type dest(
		image_type::dim_type(
			border_sz,
			border_sz
		)
	);

	sge::image::view::object const dest_view(
		dest.view()
	);

	sge::image::algorithm::fill(
		dest_view,
		sge::image::colors::transparent()
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
		sge::image::file_ptr const img(
			il->load(
				path
			)
		);

		if(img->dim() != dim)
		{
			sge::cerr << FCPPT_TEXT("some dimensions do not match!\n");
			return EXIT_FAILURE;
		}

		sge::image::algorithm::copy_and_convert(
			img->view(),
			sge::image::view::sub(
				dest_view,
				sge::image::rect(
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
		sge::image::view::make_const(
			dest_view
		)
	)->save(
		FCPPT_TEXT("out.png")
	);
}
SGE_MAINLOOP_CATCH_BLOCK
