//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/added.hpp>
#include <sge/font/added_unique_ptr.hpp>
#include <sge/font/object.hpp>
#include <sge/font/object_unique_ptr.hpp>
#include <sge/font/parameters_fwd.hpp>
#include <sge/font/system.hpp>
#include <sge/gdifont/added.hpp>
#include <sge/gdifont/object.hpp>
#include <sge/gdifont/system.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

sge::gdifont::system::system() : sge::font::system(), device_context_() {}

sge::gdifont::system::~system() {}

sge::font::object_unique_ptr
sge::gdifont::system::create_font(sge::font::parameters const &_parameters)
{
  return fcppt::unique_ptr_to_base<sge::font::object>(
      fcppt::make_unique_ptr<sge::gdifont::object>(device_context_, _parameters));
}

sge::font::added_unique_ptr sge::gdifont::system::add_font(std::filesystem::path const &_path)
{
  return fcppt::unique_ptr_to_base<sge::font::added>(
      fcppt::make_unique_ptr<sge::gdifont::added>(_path));
}
