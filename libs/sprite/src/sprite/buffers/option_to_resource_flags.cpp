//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/resource_flags.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/option_to_resource_flags.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::renderer::resource_flags_field
sge::sprite::buffers::option_to_resource_flags(sge::sprite::buffers::option const _options)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_options)
  {
  case sge::sprite::buffers::option::static_:
    return sge::renderer::resource_flags_field::null();
  case sge::sprite::buffers::option::dynamic:
    return sge::renderer::resource_flags_field{sge::renderer::resource_flags::dynamic};
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_options);
}
