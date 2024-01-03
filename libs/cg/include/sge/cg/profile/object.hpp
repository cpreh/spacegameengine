//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CG_PROFILE_OBJECT_HPP_INCLUDED
#define SGE_CG_PROFILE_OBJECT_HPP_INCLUDED

#include <sge/cg/detail/symbol.hpp>
#include <sge/cg/profile/object_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>

namespace sge::cg::profile
{

class object
{
public:
  SGE_CG_DETAIL_SYMBOL
  explicit object(CGprofile);

  [[nodiscard]] SGE_CG_DETAIL_SYMBOL CGprofile get() const;

private:
  CGprofile profile_;
};

}

#endif
