//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_MEDIA_MUXER_PARAMETERS_HPP_INCLUDED
#define SGE_MEDIA_MUXER_PARAMETERS_HPP_INCLUDED

#include <sge/media/muxer_parameters_fwd.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/media/detail/instantiate/symbol.hpp>
#include <sge/plugin/collection.hpp>
#include <fcppt/log/context_reference.hpp>

namespace sge::media
{

template <typename System>
class muxer_parameters
{
public:
  using collection_type = sge::plugin::collection<System>;

  SGE_MEDIA_DETAIL_INSTANTIATE_SYMBOL
  muxer_parameters(
      fcppt::log::context_reference, collection_type, sge::media::optional_extension_set &&);

  [[nodiscard]] SGE_MEDIA_DETAIL_INSTANTIATE_SYMBOL fcppt::log::context_reference
  log_context() const;

  [[nodiscard]] SGE_MEDIA_DETAIL_INSTANTIATE_SYMBOL collection_type const &collection() const;

  [[nodiscard]] SGE_MEDIA_DETAIL_INSTANTIATE_SYMBOL sge::media::optional_extension_set const &
  extensions() const;

private:
  fcppt::log::context_reference log_context_;

  collection_type collection_;

  sge::media::optional_extension_set extensions_;
};

}

#endif
