//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/log/default_parameters.hpp>
#include <sge/log/location.hpp>
#include <sge/plugin/capabilities.hpp>
#include <sge/plugin/category_array.hpp>
#include <sge/plugin/context_base_ref.hpp>
#include <sge/plugin/context_base_unique_ptr.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/optional_cache_ref_fwd.hpp>
#include <sge/plugin/impl/context_base.hpp>
#include <sge/plugin/impl/load_plugins.hpp>
#include <sge/plugin/impl/log_name.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/enum/array_impl.hpp>
#include <fcppt/enum/array_init.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::plugin::manager::manager(
    fcppt::log::context_reference const _log_context,
    std::filesystem::path const &_path,
    sge::plugin::optional_cache_ref const &_cache)
    : log_{_log_context, sge::log::location(), sge::log::default_parameters(sge::plugin::impl::log_name())},
      plugins_(
          [this, &_path, &_cache]
          {
            FCPPT_LOG_DEBUG(
                this->log_,
                fcppt::log::out << FCPPT_TEXT("Scanning for plugins in ")
                                << fcppt::filesystem::path_to_string(_path))

            return sge::plugin::impl::load_plugins(this->log_, _path, _cache);
          }()),
      categories_(fcppt::enum_::array_init<sge::plugin::manager::plugin_map>(
          [this](sge::plugin::capabilities const _capability)
          {
            return fcppt::algorithm::map_optional<sge::plugin::category_array>(
                plugins_,
                [_capability](sge::plugin::context_base_unique_ptr const &_context)
                {
                  using optional_result = fcppt::optional::object<sge::plugin::context_base_ref>;

                  return _context->info().capabilities() & _capability
                             ? optional_result(fcppt::make_ref(*_context))
                             : optional_result();
                });
          }))
{
}

FCPPT_PP_POP_WARNING

sge::plugin::manager::~manager() = default;
