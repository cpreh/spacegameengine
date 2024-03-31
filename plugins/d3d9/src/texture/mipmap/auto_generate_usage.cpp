//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/texture/mipmap/auto_generate_usage.hpp>
#include <sge/renderer/texture/mipmap/auto_generate.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/to_unsigned_fun.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::d3d9::usage const sge::d3d9::texture::mipmap::auto_generate_usage(
    sge::renderer::texture::mipmap::auto_generate const _value)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_value)
  {
  case sge::renderer::texture::mipmap::auto_generate::yes:
    return fcppt::strong_typedef_construct_cast<sge::d3d9::usage, fcppt::cast::to_unsigned_fun>(
        D3DUSAGE_AUTOGENMIPMAP);
  case sge::renderer::texture::mipmap::auto_generate::no:
    return sge::d3d9::usage(0u);
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_value);
}
