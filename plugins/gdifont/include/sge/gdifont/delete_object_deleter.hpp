//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GDIFONT_DELETE_OBJECT_DELETER_HPP_INCLUDED
#define SGE_GDIFONT_DELETE_OBJECT_DELETER_HPP_INCLUDED

#include <sge/gdifont/delete_object_deleter_fwd.hpp>
#include <sge/gdifont/include_windows.hpp>

namespace sge
{
namespace gdifont
{

struct delete_object_deleter
{
  void operator()(HGDIOBJ) const noexcept;
};

}
}

#endif
