//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RUCKSACK_TESTBED_IMPL_OBJECT_IMPL_HPP_INCLUDED
#define SGE_RUCKSACK_TESTBED_IMPL_OBJECT_IMPL_HPP_INCLUDED

#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/testbed/systems.hpp>
#include <sge/rucksack/widget/reference.hpp>
#include <sge/sprite/object_decl.hpp>
#include <sge/sprite/buffers/single_decl.hpp>
#include <sge/sprite/buffers/with_declaration_decl.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/pos.hpp>
#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_color.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object_decl.hpp>
#include <sge/sprite/state/parameters_fwd.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge::rucksack::testbed
{

class object_impl
{
  FCPPT_NONMOVABLE(object_impl);

public:
  explicit object_impl(sge::window::title &&);

  void add_widget(sge::rucksack::widget::reference, sge::image::color::any::object const &);

  [[nodiscard]] awl::main::exit_code run();

  void update();

  void render(sge::renderer::context::ffp & // NOLINT(google-runtime-references)
  ); // NOLINT(google-runtime-references)

  [[nodiscard]] sge::rucksack::testbed::systems const &systems() const;

  ~object_impl();

private:
  using color_format = sge::image::color::rgba8_format;

  using sprite_choices = sge::sprite::config::choices<
      sge::sprite::config::type_choices<
          sge::sprite::config::unit_type<sge::rucksack::scalar>,
          sge::sprite::config::float_type<float>>,
      sge::sprite::config::pos<sge::sprite::config::pos_option::pos>,
      sge::sprite::config::normal_size<sge::sprite::config::texture_size_option::never>,
      fcppt::mpl::list::object<sge::sprite::config::with_color<color_format>>>;

  using sprite_buffers =
      sge::sprite::buffers::with_declaration<sge::sprite::buffers::single<sprite_choices>>;

  using sprite_object = sge::sprite::object<sprite_choices>;

  using sprite_state_choices = sge::sprite::state::all_choices;

  using sprite_state_object = sge::sprite::state::object<sprite_state_choices>;

  using sprite_state_parameters = sge::sprite::state::parameters<sprite_state_choices>;

  using sprite_list = std::vector<std::pair<sge::rucksack::widget::reference, sprite_object>>;

  sge::rucksack::testbed::systems const systems_;

  sprite_buffers buffers_;

  sprite_state_object sprite_states_;

  sprite_list sprites_;
};

}

#endif
