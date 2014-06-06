/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/config/plugin_path.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/optional_file_unique_ptr.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/system_unique_ptr.hpp>
#include <sge/image2d/algorithm/compare.hpp>
#include <sge/image2d/plugin/object.hpp>
#include <sge/image2d/store/rgba8.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/media/optional_extension.hpp>
#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/optional_cache_ref.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/test/unit_test.hpp>
#include <sstream>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	rgba
)
{
FCPPT_PP_POP_WARNING
	typedef
	sge::image2d::store::rgba8
	store_type;

	store_type store(
		store_type::dim(
			1,
			1
		)
	);

	typedef
	store_type::wrapped_view_type
	view_type;

	store.wrapped_view()[
		view_type::dim(
			0,
			0
		)
	] =
		sge::image::color::rgba8(
			(sge::image::color::init::red() %= 0.5)
			(sge::image::color::init::blue() %= 0.3)
			(sge::image::color::init::green() %= 0.2)
			(sge::image::color::init::alpha() %= 0.1)
		);

	sge::plugin::manager plugins(
		sge::config::plugin_path(),
		sge::plugin::optional_cache_ref()
	);

	for(
		auto const &element
		:
		plugins.collection<
			sge::image2d::system
		>()
	)
	{
		sge::image2d::plugin::object const plugin(
			element.load()
		);

		sge::image2d::system_unique_ptr const system(
			plugin.get()()
		);

		std::stringstream stream;

		sge::image2d::optional_file_unique_ptr const created(
			system->create(
				sge::image2d::view::const_object(
					store.const_wrapped_view()
				),
				sge::media::optional_extension()
			)
		);

		BOOST_REQUIRE(
			created
		);

		(*created)->save_stream(
			stream
		);

		sge::image2d::optional_file_unique_ptr const file(
			system->load_stream(
				stream,
				sge::media::optional_extension()
			)
		);

		BOOST_REQUIRE(
			file
		);

		BOOST_CHECK(
			sge::image2d::algorithm::compare(
				sge::image2d::view::const_object(
					store.const_wrapped_view()
				),
				(*file)->view()
			)
		);
	}
}
