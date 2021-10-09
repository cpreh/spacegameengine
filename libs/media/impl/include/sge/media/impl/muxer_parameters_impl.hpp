//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_MEDIA_IMPL_MUXER_PARAMETERS_IMPL_HPP_INCLUDED
#define SGE_MEDIA_IMPL_MUXER_PARAMETERS_IMPL_HPP_INCLUDED

#include <sge/media/muxer_parameters.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

template <typename System>
sge::media::muxer_parameters<System>::muxer_parameters(
    fcppt::log::context_reference const _log_context,
    collection_type _collection,
    sge::media::optional_extension_set &&_extensions)
    : log_context_(_log_context),
      collection_(std::move(_collection)),
      extensions_(std::move(_extensions))
{
}

template <typename System>
fcppt::log::context_reference sge::media::muxer_parameters<System>::log_context() const
{
  return log_context_;
}

template <typename System>
typename sge::media::muxer_parameters<System>::collection_type const &
sge::media::muxer_parameters<System>::collection() const
{
  return collection_;
}

template <typename System>
sge::media::optional_extension_set const &sge::media::muxer_parameters<System>::extensions() const
{
  return extensions_;
}

#endif
