//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VF_VERTEX_DECL_HPP_INCLUDED
#define SGE_RENDERER_VF_VERTEX_DECL_HPP_INCLUDED

#include <sge/renderer/vf/vertex_fwd.hpp>
#include <sge/renderer/vf/detail/vertex.hpp>
#include <fcppt/record/enable_vararg_ctor.hpp>
#include <fcppt/record/label_value_type.hpp>
#include <fcppt/record/object_impl.hpp>

namespace sge::renderer::vf
{

template <typename Part>
class vertex
{
public:
  using format_part = Part;

  using record_type = typename sge::renderer::vf::detail::vertex<Part>::type;

  template <typename... Args, typename = fcppt::record::enable_vararg_ctor<Args...>>
  explicit vertex(Args &&...);

  template <typename Label>
  [[nodiscard]] fcppt::record::label_value_type<record_type, Label> const &get() const;

  template <typename Label>
  void set(fcppt::record::label_value_type<record_type, Label> const &);

private:
  record_type elements_;
};

}

#endif
