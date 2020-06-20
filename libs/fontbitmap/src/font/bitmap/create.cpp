//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/object.hpp>
#include <sge/font/object_unique_ptr.hpp>
#include <sge/font/bitmap/create.hpp>
#include <sge/font/bitmap/impl/object.hpp>
#include <sge/image2d/system_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


sge::font::object_unique_ptr
sge::font::bitmap::create(
	fcppt::log::context_reference const _log_context,
	std::filesystem::path const &_path,
	sge::image2d::system_ref const _system
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::font::object
		>(
			fcppt::make_unique_ptr<
				sge::font::bitmap::impl::object
			>(
				_log_context,
				_path,
				_system
			)
		);
}
