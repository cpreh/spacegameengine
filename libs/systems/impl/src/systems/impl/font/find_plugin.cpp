//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/plugin/collection.hpp>
#include <sge/font/plugin/context.hpp>
#include <sge/font/plugin/iterator.hpp>
#include <sge/font/plugin/object.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/name.hpp>
#include <sge/systems/exception.hpp>
#include <sge/systems/font.hpp>
#include <sge/systems/optional_name.hpp>
#include <sge/systems/impl/font/find_plugin.hpp>
#include <fcppt/const.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_comparison.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/find_if_opt.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/to_exception.hpp>

sge::font::plugin::object sge::systems::impl::font::find_plugin(
    sge::font::plugin::collection const &_collection, sge::systems::font const &_parameters)
{
  sge::systems::optional_name const &name{_parameters.name()};

  return fcppt::optional::to_exception(
             fcppt::optional::map(
                 fcppt::algorithm::find_if_opt(
                     _collection,
                     [&name](sge::font::plugin::context const &_plugin)
                     {
                       return fcppt::optional::maybe(
                           name,
                           fcppt::const_(true),
                           [&_plugin](sge::plugin::name const &_name)
                           { return _name == _plugin.info().name(); });
                     }),
                 [](sge::font::plugin::iterator const &_iterator) -> sge::font::plugin::context
                 { return *_iterator; }),
             [&name]
             {
               return sge::systems::exception{fcppt::optional::maybe(
                   name,
                   [] {
                     return fcppt::string{FCPPT_TEXT("No plugin of type sge::font::system found!")};
                   },
                   [](sge::plugin::name const &_name)
                   {
                     return FCPPT_TEXT("No plugin of type sge::font::system with name ") +
                            _name.get() + FCPPT_TEXT(" found!");
                   })};
             })
      .load();
}
