//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_IMPL_MULTI_SYSTEM_HPP_INCLUDED
#define SGE_INPUT_IMPL_MULTI_SYSTEM_HPP_INCLUDED

#include <sge/input/capabilities_field.hpp>
#include <sge/input/processor_unique_ptr.hpp>
#include <sge/input/system.hpp>
#include <sge/input/impl/system_ptr_vector.hpp>
#include <sge/input/plugin/collection_fwd.hpp>
#include <sge/input/plugin/object.hpp>
#include <sge/plugin/manager_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge::input::impl
{

class multi_system : public sge::input::system
{
  FCPPT_NONMOVABLE(multi_system);

public:
  multi_system(fcppt::log::context_reference, sge::input::plugin::collection const &);

  ~multi_system() override;

private:
  [[nodiscard]] sge::input::processor_unique_ptr create_processor(sge::window::object_ref) override;

  [[nodiscard]] sge::input::capabilities_field capabilities() const override;

  fcppt::log::object log_;

  using plugin_vector = std::vector<sge::input::plugin::object>;

  plugin_vector plugins_;

  sge::input::impl::system_ptr_vector systems_;

  sge::input::capabilities_field capabilities_;
};

}

#endif
