//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/loader.hpp>
#include <sge/audio/loader_plugin/collection.hpp> // NOLINT(misc-include-cleaner)
#include <sge/audio/loader_plugin/context.hpp> // NOLINT(misc-include-cleaner)
#include <sge/audio/loader_plugin/iterator.hpp> // NOLINT(misc-include-cleaner)
#include <sge/audio/loader_plugin/traits.hpp> // NOLINT(misc-include-cleaner)
#include <sge/plugin/impl/instantiate_collection.hpp>

SGE_PLUGIN_IMPL_INSTANTIATE_COLLECTION(sge::audio::loader);
