//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_IMPL_LOAD_PLUGINS_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_LOAD_PLUGINS_HPP_INCLUDED

#include <sge/plugin/optional_cache_ref_fwd.hpp>
#include <sge/plugin/detail/context_base_vector.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace plugin
{
namespace impl
{

sge::plugin::detail::context_base_vector
load_plugins(
	fcppt::log::object &, // NOLINT(google-runtime-references)
	std::filesystem::path const &,
	sge::plugin::optional_cache_ref const &
);

}
}
}

#endif
