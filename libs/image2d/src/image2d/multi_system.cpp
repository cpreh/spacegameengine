//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image2d/file.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image2d/load_stream_result.hpp>
#include <sge/image2d/multi_system.hpp>
#include <sge/image2d/multi_system_parameters.hpp>
#include <sge/image2d/optional_file_unique_ptr.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/plugin/collection.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image2d/plugin/context.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image2d/plugin/iterator.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image2d/plugin/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image2d/plugin/traits.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image2d/view/const_object.hpp>
#include <sge/media/extension_fwd.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/media/stream_unique_ptr.hpp>
#include <sge/media/impl/muxer_impl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::image2d::multi_system::multi_system(sge::image2d::multi_system_parameters const &_params)
    : sge::image2d::system(), muxer_(_params)
{
}

sge::image2d::multi_system::~multi_system() = default;

sge::image2d::load_stream_result sge::image2d::multi_system::load_stream(
    sge::media::stream_unique_ptr &&_stream,
    sge::media::optional_extension const &_extension,
    sge::media::optional_name const &_name)
{
  return muxer_.mux_stream(std::move(_stream), _extension, _name);
}

sge::image2d::optional_file_unique_ptr sge::image2d::multi_system::create(
    sge::image2d::view::const_object const &_view, sge::media::extension const &_extension)
{
  return fcppt::optional::bind(
      muxer_.mux_extension(_extension),
      [&_view, &_extension](fcppt::reference<sge::image2d::system> const _system)
      { return _system.get().create(_view, _extension); });
}

sge::media::extension_set sge::image2d::multi_system::extensions() const
{
  return muxer_.extensions();
}
