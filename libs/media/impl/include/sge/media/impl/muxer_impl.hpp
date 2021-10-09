//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_MEDIA_IMPL_MUXER_IMPL_HPP_INCLUDED
#define SGE_MEDIA_IMPL_MUXER_IMPL_HPP_INCLUDED

#include <sge/media/extension_fwd.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/load_stream_result.hpp>
#include <sge/media/muxer.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/media/stream_unique_ptr.hpp>
#include <sge/media/impl/detail/muxer_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/optional/reference.hpp>

template <typename System, typename File>
sge::media::muxer<System, File>::muxer(parameters const &_parameters)
    : impl_(fcppt::make_unique_ptr<muxer_impl>(_parameters))
{
}

namespace sge::media
{
template <typename System, typename File>
muxer<System, File>::~muxer() = default;
}

template <typename System, typename File>
typename sge::media::muxer<System, File>::load_stream_result
sge::media::muxer<System, File>::mux_stream(
    sge::media::stream_unique_ptr &&_stream,
    sge::media::optional_extension const &_extension,
    sge::media::optional_name const &_name) const
{
  return impl_->mux_stream(std::move(_stream), _extension, _name);
}

template <typename System, typename File>
typename sge::media::muxer<System, File>::optional_system_ref
sge::media::muxer<System, File>::mux_extension(sge::media::extension const &_extension) const
{
  return impl_->mux_extension(_extension);
}

template <typename System, typename File>
sge::media::extension_set sge::media::muxer<System, File>::extensions() const
{
  return impl_->extensions();
}

#endif
