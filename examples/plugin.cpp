//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/loader.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/loader_plugin/collection.hpp> // NOLINT(misc-include-cleaner)
#include <sge/audio/loader_plugin/context.hpp> // NOLINT(misc-include-cleaner)
#include <sge/audio/loader_plugin/iterator.hpp> // NOLINT(misc-include-cleaner)
#include <sge/audio/loader_plugin/manager.hpp> // NOLINT(misc-include-cleaner)
#include <sge/audio/player_plugin/collection.hpp> // NOLINT(misc-include-cleaner)
#include <sge/audio/player_plugin/context.hpp> // NOLINT(misc-include-cleaner)
#include <sge/audio/player_plugin/iterator.hpp> // NOLINT(misc-include-cleaner)
#include <sge/audio/player_plugin/manager.hpp> // NOLINT(misc-include-cleaner)
#include <sge/config/plugin_path.hpp>
#include <sge/font/system.hpp>
#include <sge/font/plugin/collection.hpp> // NOLINT(misc-include-cleaner)
#include <sge/font/plugin/context.hpp> // NOLINT(misc-include-cleaner)
#include <sge/font/plugin/iterator.hpp> // NOLINT(misc-include-cleaner)
#include <sge/font/plugin/manager.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image2d/system.hpp>
#include <sge/image2d/plugin/collection.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image2d/plugin/context.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image2d/plugin/iterator.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image2d/plugin/manager.hpp> // NOLINT(misc-include-cleaner)
#include <sge/input/system.hpp>
#include <sge/input/plugin/collection.hpp> // NOLINT(misc-include-cleaner)
#include <sge/input/plugin/context.hpp> // NOLINT(misc-include-cleaner)
#include <sge/input/plugin/iterator.hpp> // NOLINT(misc-include-cleaner)
#include <sge/input/plugin/manager.hpp> // NOLINT(misc-include-cleaner)
#include <sge/log/default_level_streams.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/optional_cache_ref.hpp>
#include <sge/renderer/core.hpp>
#include <sge/renderer/plugin/collection.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/plugin/context.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/plugin/iterator.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/plugin/manager.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/tag_type.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/use.hpp>
#include <fcppt/algorithm/loop.hpp>
#include <fcppt/algorithm/loop_break_mpl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/optional_level.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <typeinfo> // NOLINT(misc-include-cleaner)
#include <fcppt/config/external_end.hpp>

int main()
try
{
  fcppt::log::context log_context(
      fcppt::log::optional_level{fcppt::log::level::debug}, sge::log::default_level_streams());

  sge::plugin::manager manager(
      fcppt::make_ref(log_context), sge::config::plugin_path(), sge::plugin::optional_cache_ref());

  using plugins = fcppt::mpl::list::object<
      sge::audio::loader,
      sge::audio::player,
      sge::font::system,
      sge::image2d::system,
      sge::input::system,
      sge::renderer::core>;

  fcppt::algorithm::loop(
      plugins{},
      [&manager](auto const _tag)
      {
        FCPPT_USE(_tag);

        using type = fcppt::tag_type<decltype(_tag)>;

        fcppt::io::cout() << fcppt::from_std_string(fcppt::type_name_from_info(typeid(type)))
                          << FCPPT_TEXT('\n');

        for (auto const &plugin : manager.collection<type>())
        {
          sge::plugin::info const &info(plugin.info());

          fcppt::io::cout() << FCPPT_TEXT("\tname: \"") << info.name()
                            << FCPPT_TEXT("\", description: \"") << info.description()
                            << FCPPT_TEXT("\"\n");
        }
      });
}
catch (fcppt::exception const &_exception)
{
  fcppt::io::cerr() << _exception.string() << FCPPT_TEXT('\n');

  return EXIT_FAILURE;
}
catch (std::exception const &_exception)
{
  std::cerr << _exception.what() << '\n';

  return EXIT_FAILURE;
}
