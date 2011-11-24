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


#include <sge/exception.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/store.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_ptr.hpp>
#include <sge/image2d/rgba8.hpp>
#include <sge/image2d/save_from_view.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/algorithm/fill.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/sub.hpp>
#include <sge/image2d/view/to_const.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/filesystem/directory_iterator.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::renderer::size_type
calc_size(
	sge::renderer::size_type const _image_count,
	sge::renderer::dim2 const &_dim
)
{
	for(
		sge::renderer::size_type index(0);
		index <= 10;
		++index
	)
	{
		sge::renderer::size_type const size(
			1u << index
		);

		if(
			(size / (_dim.w() + 1))
			* (size / (_dim.h() + 1))
			>= _image_count
		)
			return size;
	}

	throw sge::exception(
		FCPPT_TEXT("size too big!")
	);
}

sge::renderer::dim2 const
first_dim(
	fcppt::filesystem::path const &_path,
	sge::image2d::system &_system
)
{
	fcppt::filesystem::directory_iterator const it(
		_path
	);

	return
		_system.load(
			*it
		)->size();
}

typedef std::vector<
	fcppt::filesystem::path
> path_vector;

path_vector const
sort_paths(
	fcppt::filesystem::path const &_path
)
{
	path_vector ret;

	std::copy(
		fcppt::filesystem::directory_iterator(
			_path
		),
		fcppt::filesystem::directory_iterator(),
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

int
main(
	int argc,
	char **argv
)
try
{
	if(
		argc != 2
	)
	{
		fcppt::io::cerr()
			<< FCPPT_TEXT("please specify a path!\n");

		return EXIT_FAILURE;
	}

	sge::systems::instance const sys(
		(
			sge::systems::list
			(
				sge::systems::image2d(
					sge::image::capabilities_field::null(),
					fcppt::assign::make_container<
						sge::media::extension_set
					>(
						sge::media::extension(
							FCPPT_TEXT("png")
						)
					)
				)
			)
		)
	);

	sge::image2d::system &il(
		sys.image_system()
	);

	fcppt::filesystem::path const path(
		fcppt::from_std_string(
			argv[1]
		)
	);

	sge::renderer::size_type const image_count(
		static_cast<
			sge::renderer::size_type
		>(
			std::distance(
				fcppt::filesystem::directory_iterator(
					path
				),
				fcppt::filesystem::directory_iterator()
			)
		)
	);

	if(
		image_count == 0
	)
	{
		fcppt::io::cerr()
			<< FCPPT_TEXT("No files here.\n");

		return EXIT_SUCCESS;
	}

	sge::renderer::dim2 const dim(
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

	typedef sge::image2d::rgba8 image_type;

	image_type dest(
		image_type::dim(
			border_sz,
			border_sz
		)
	);

	sge::image2d::view::object const dest_view(
		dest.wrapped_view()
	);

	sge::image2d::algorithm::fill(
		dest_view,
		sge::image::colors::transparent()
	);

	sge::image2d::rect::vector pos(
		sge::image2d::rect::vector::null()
	);

	path_vector const paths(
		sort_paths(
			path
		)
	);

	for(
		path_vector::const_iterator cur_path_it(
			paths.begin()
		);
		cur_path_it != paths.end();
		++cur_path_it
	)
	{
		sge::image2d::file_ptr const img(
			il.load(
				*cur_path_it
			)
		);

		if(
			img->size() != dim
		)
		{
			fcppt::io::cerr()
				<< FCPPT_TEXT("some dimensions do not match!\n");

			return EXIT_FAILURE;
		}

		sge::image2d::algorithm::copy_and_convert(
			img->view(),
			sge::image2d::view::sub(
				dest_view,
				sge::image2d::rect(
					pos,
					dim
				)
			),
			sge::image::algorithm::may_overlap::no
		);

		pos.x() += dim.w() + 1;

		if(
			pos.x() + dim.w() + 1 > border_sz
		)
		{
			pos.x() = 0;
			pos.y() += dim.h() + 1;
		}
	}

	sge::image2d::save_from_view(
		il,
		sge::image2d::view::to_const(
			dest_view
		),
		FCPPT_TEXT("out.png")
	);
}
catch(
	std::exception const &_exception
)
{
	std::cerr
		<< _exception.what()
		<< '\n';

	return EXIT_FAILURE;
}
