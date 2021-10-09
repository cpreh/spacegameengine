//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image2d/multi_system.hpp>
#include <sge/image2d/multi_system_parameters.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/image2d/plugin/collection_fwd.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/impl/image2d/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/log/context_reference.hpp>

sge::systems::impl::image2d::object::object(
    fcppt::log::context_reference const _log_context,
    sge::image2d::plugin::collection const &_collection,
    sge::systems::image2d const &_parameters)
    : image_multi_system_(
          fcppt::make_unique_ptr<sge::image2d::multi_system>(sge::image2d::multi_system_parameters{
              _log_context,
              _collection,
              sge::media::optional_extension_set{_parameters.extensions()}}))
{
}

sge::systems::impl::image2d::object::~object() = default;

sge::image2d::system &sge::systems::impl::image2d::object::system() const
{
  return *image_multi_system_;
}
