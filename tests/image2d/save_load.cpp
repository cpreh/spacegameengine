/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <sge/image/view/wrap.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_unique_ptr.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/system_unique_ptr.hpp>
#include <sge/image2d/algorithm/compare.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/algorithm/print.hpp>
#include <sge/image2d/plugin/object.hpp>
#include <sge/image2d/store/rgba8.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/format.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/media/optional_extension.hpp>
#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/optional_cache_ref.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/math/dim/comparison.hpp>
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

	store_type const store{
		store_type::dim(
			1u,
			1u
		),
		sge::image::color::rgba8(
			(sge::image::color::init::red() %= 0.5)
			(sge::image::color::init::blue() %= 0.3)
			(sge::image::color::init::green() %= 0.2)
			(sge::image::color::init::alpha() %= 0.1)
		)
	};

	sge::plugin::manager plugins(
		sge::config::plugin_path(),
		sge::plugin::optional_cache_ref()
	);

	for(
		sge::plugin::context<
			sge::image2d::system
		> const &element
		:
		plugins.collection<
			sge::image2d::system
		>()
	)
	{
		fcppt::io::cout()
			<<
			FCPPT_TEXT("Testing plugin ")
			<<
			element.info().name()
			<<
			FCPPT_TEXT('\n');

		sge::image2d::plugin::object const plugin(
			element.load()
		);

		sge::image2d::system_unique_ptr const system(
			plugin.get()()
		);

		std::stringstream stream;

		sge::image2d::view::const_object const source_view(
			sge::image2d::view::const_object(
				store.const_wrapped_view()
			)
		);

		sge::image2d::file_unique_ptr const created(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				system->create(
					source_view,
					sge::media::optional_extension()
				)
			)
		);

		created->save_stream(
			stream
		);

		sge::image2d::file_unique_ptr const file(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				system->load_stream(
					stream,
					sge::media::optional_extension()
				)
			)
		);

		sge::image2d::view::const_object const dest_view(
			file->view()
		);

		BOOST_REQUIRE(
			sge::image2d::view::size(
				source_view
			)
			==
			sge::image2d::view::size(
				dest_view
			)
		);

		store_type const store_back{
			store.size(),
			[
				&dest_view
			](
				store_type::view_type const &_dest
			)
			{
				sge::image2d::algorithm::copy_and_convert(
					dest_view,
					sge::image2d::view::object(
						sge::image::view::wrap(
							_dest
						)
					),
					sge::image::algorithm::may_overlap::no,
					sge::image::algorithm::uninitialized::yes
				);
			}
		};

		sge::image2d::view::const_object const store_back_view(
			sge::image2d::view::const_object(
				store_back.const_wrapped_view()
			)
		);

		fcppt::io::cout()
			<<
			FCPPT_TEXT("Old store is :");

		sge::image2d::algorithm::print(
			fcppt::io::cout(),
			source_view
		);

		fcppt::io::cout()
			<< FCPPT_TEXT('\n');

		fcppt::io::cout()
			<<
			FCPPT_TEXT("New store is :");

		sge::image2d::algorithm::print(
			fcppt::io::cout(),
			store_back_view
		);

		fcppt::io::cout()
			<< FCPPT_TEXT('\n');

		BOOST_CHECK(
			sge::image2d::algorithm::compare(
				source_view,
				store_back_view
			)
		);
	}
}
