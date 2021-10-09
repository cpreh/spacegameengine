//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_IMPL_AUDIO_LOADER_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_AUDIO_LOADER_HPP_INCLUDED

#include <sge/audio/multi_loader_fwd.hpp>
#include <sge/audio/loader_plugin/collection_fwd.hpp>
#include <sge/systems/audio_loader_fwd.hpp>
#include <sge/systems/impl/audio/loader_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/context_reference_fwd.hpp>

namespace sge::systems::impl::audio
{

class loader
{
  FCPPT_NONMOVABLE(loader);

public:
  loader(
      fcppt::log::context_reference,
      sge::audio::loader_plugin::collection const &,
      sge::systems::audio_loader const &);

  ~loader();

  [[nodiscard]] sge::audio::loader &get() const;

private:
  using audio_multi_loader_ptr = fcppt::unique_ptr<sge::audio::multi_loader>;

  audio_multi_loader_ptr const audio_multi_loader_;
};

}

#endif
