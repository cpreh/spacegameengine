//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/bvh/dummy_node.hpp>
#include <sge/bvh/object_impl.hpp>
#include <sge/bvh/tree_traits.hpp>
#include <sge/image/channel8.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <sge/input/key/code.hpp>
#include <sge/input/keyboard/event/key.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/event/render.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/onscreen.hpp> // NOLINT(misc-include-cleaner)
#include <sge/sprite/object.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single.hpp>
#include <sge/sprite/buffers/with_declaration.hpp>
#include <sge/sprite/compare/default.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/pos.hpp>
#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_color.hpp>
#include <sge/sprite/geometry/make_random_access_range.hpp>
#include <sge/sprite/process/all.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object.hpp>
#include <sge/sprite/state/parameters.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/window_source.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/loop.hpp>
#include <sge/window/loop_function.hpp>
#include <sge/window/title.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/show_message.hpp>
#include <awl/event/base.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/exit_success.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/const.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/strong_typedef_output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/container/tree/depth.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/math/box/object.hpp>
#include <fcppt/math/box/output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/default_help_switch.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/error_output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/parse_help.hpp>
#include <fcppt/options/result.hpp>
#include <fcppt/options/result_of.hpp>
#include <fcppt/options/usage.hpp>
#include <fcppt/options/usage_output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_real.hpp>
#include <fcppt/random/generator/minstd_rand.hpp>
#include <fcppt/random/generator/seed_from_chrono.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/record/object_impl.hpp>
#include <fcppt/record/permute.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/get_unsafe.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/variant/output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/variant/to_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <example_main.hpp>
#include <chrono>
#include <exception>
#include <iostream>
#include <ostream>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace
{

using sprite_choices = sge::sprite::config::choices<
    sge::sprite::config::type_choices<
        sge::sprite::config::unit_type<sge::renderer::scalar>,
        sge::sprite::config::float_type<sge::renderer::scalar>>,
    sge::sprite::config::pos<sge::sprite::config::pos_option::pos>,
    sge::sprite::config::normal_size<sge::sprite::config::texture_size_option::never>,
    fcppt::mpl::list::object<sge::sprite::config::with_color<sge::image::color::rgba8_format>>>;

using sprite_buffers_type =
    sge::sprite::buffers::with_declaration<sge::sprite::buffers::single<sprite_choices>>;

using sprite_object = sge::sprite::object<sprite_choices>;

using sprite_state_choices = sge::sprite::state::all_choices;

using sprite_state_object = sge::sprite::state::object<sprite_state_choices>;

using sprite_state_parameters = sge::sprite::state::parameters<sprite_state_choices>;

using bvh_box = fcppt::math::box::object<sge::renderer::scalar, 2>;

using bvh_tree_traits = sge::bvh::tree_traits<sge::bvh::dummy_node, bvh_box, bvh_box>;

using sprite_sequence = std::vector<sprite_object>;

sprite_object create_sprite(bvh_box const &_rect, sge::image::color::rgba8 const &_color)
{
  return sprite_object(
      sge::sprite::roles::pos{} = _rect.pos(),
      sge::sprite::roles::color{} = _color,
      sge::sprite::roles::size{} = _rect.size());
}

class bvh_traverser
{
  FCPPT_NONMOVABLE(bvh_traverser);

public:
  explicit bvh_traverser(bvh_tree_traits::tree_representation const &_tree)
      : tree_{_tree}, current_tree_(fcppt::make_cref(tree_))
  {
  }

  ~bvh_traverser() = default;

  [[nodiscard]] sprite_sequence sprites() const
  {
    bvh_tree_traits::tree_representation const &tree{
        fcppt::optional::to_exception(
            current_tree_, [] { return fcppt::exception{FCPPT_TEXT("No current tree.")}; })
            .get()};

    // First, render the background
    sprite_sequence result{create_sprite(
        fcppt::variant::get_unsafe<bvh_tree_traits::node_wrapper>(tree.value()).bounding_box(),
        sge::image::color::rgba8{
            // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
            (sge::image::color::init::red() = fcppt::literal<sge::image::channel8>(0x2eU))
            // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
            (sge::image::color::init::green() = fcppt::literal<sge::image::channel8>(0x26U))
            // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
            (sge::image::color::init::blue() = fcppt::literal<sge::image::channel8>(0x21U))
            // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
            (sge::image::color::init::alpha() = fcppt::literal<sge::image::channel8>(255U))})};

    fcppt::optional::maybe_void(
        fcppt::optional::bind(
            tree.front(),
            [](fcppt::reference<bvh_tree_traits::tree_representation const> const _front) {
              return fcppt::variant::to_optional<bvh_tree_traits::node_wrapper>(
                  _front.get().value());
            }),
        [&result](bvh_tree_traits::node_wrapper const &_wrapper)
        {
          result.push_back(create_sprite(
              _wrapper.bounding_box(),
              sge::image::color::rgba8{
                  // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  (sge::image::color::init::red() = fcppt::literal<sge::image::channel8>(0xbeU))
                  // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  (sge::image::color::init::green() = fcppt::literal<sge::image::channel8>(0xe8U))
                  // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  (sge::image::color::init::blue() = fcppt::literal<sge::image::channel8>(0xe0U))
                  // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  (sge::image::color::init::alpha() = fcppt::literal<sge::image::channel8>(255U))}));
        });

    fcppt::optional::maybe_void(
        fcppt::optional::bind(
            tree.back(),
            [](fcppt::reference<bvh_tree_traits::tree_representation const> const _back) {
              return fcppt::variant::to_optional<bvh_tree_traits::node_wrapper>(
                  _back.get().value());
            }),
        [&result](bvh_tree_traits::node_wrapper const &_wrapper)
        {
          result.push_back(create_sprite(
              _wrapper.bounding_box(),
              sge::image::color::rgba8{
                  // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  (sge::image::color::init::red() = fcppt::literal<sge::image::channel8>(0xffU))
                  // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  (sge::image::color::init::green() = fcppt::literal<sge::image::channel8>(0x5eU))
                  // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  (sge::image::color::init::blue() = fcppt::literal<sge::image::channel8>(0x00U))
                  // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  (sge::image::color::init::alpha() = fcppt::literal<sge::image::channel8>(255U))}));
        });

    fcppt::optional::maybe_void(
        tree.front(),
        [&result, this](fcppt::reference<bvh_tree_traits::tree_representation const> const _front)
        {
          this->add_children(
              fcppt::make_ref(result),
              _front.get(),
              sge::image::color::rgba8{
                  // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  (sge::image::color::init::red() = fcppt::literal<sge::image::channel8>(0x37U))
                  // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  (sge::image::color::init::green() = fcppt::literal<sge::image::channel8>(0x3cU))
                  // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  (sge::image::color::init::blue() = fcppt::literal<sge::image::channel8>(0x40U))
                  // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  (sge::image::color::init::alpha() = fcppt::literal<sge::image::channel8>(255U))});
        });

    fcppt::optional::maybe_void(
        tree.back(),
        [&result, this](fcppt::reference<bvh_tree_traits::tree_representation const> const _back)
        {
          this->add_children(
              fcppt::make_ref(result),
              _back.get(),
              sge::image::color::rgba8{
                  // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  (sge::image::color::init::red() = fcppt::literal<sge::image::channel8>(0x73U))
                  // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  (sge::image::color::init::green() = fcppt::literal<sge::image::channel8>(0x32U))
                  // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  (sge::image::color::init::blue() = fcppt::literal<sge::image::channel8>(0x0bU))
                  // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  (sge::image::color::init::alpha() = fcppt::literal<sge::image::channel8>(255U))});
        });

    return result;
  }

  void key_event(sge::input::keyboard::event::key const &_event)
  {
    bvh_tree_traits::tree_representation const &tree{
        fcppt::optional::to_exception(
            current_tree_, [] { return fcppt::exception{FCPPT_TEXT("No current tree.")}; })
            .get()};

    if (!_event.pressed())
    {
      return;
    }

    auto const make_tree(
        [&tree, &_event]
        {
          FCPPT_PP_PUSH_WARNING
          FCPPT_PP_DISABLE_CLANG_WARNING(-Wswitch-enum)

          switch (_event.get().code())
          {
          case sge::input::key::code::left:
            return tree.front();
          case sge::input::key::code::right:
            return tree.back();
          case sge::input::key::code::up:
            return tree.front();
          case sge::input::key::code::down:
            return tree.back();
          case sge::input::key::code::p:
            return tree.parent();
          default:
            return bvh_tree_traits::tree_representation::const_optional_ref{};
          }

          FCPPT_PP_POP_WARNING
        });

    bvh_tree_traits::tree_representation::const_optional_ref const new_tree{make_tree()};

    if (fcppt::optional::maybe(
            new_tree,
            fcppt::const_(true),
            [](fcppt::reference<bvh_tree_traits::tree_representation const> const _new_tree)
            { return _new_tree.get().empty(); }))
    {
      return;
    }

    current_tree_ = new_tree;
  }

private:
  bvh_tree_traits::tree_representation const &tree_;

  bvh_tree_traits::tree_representation::const_optional_ref current_tree_;

  void add_children(
      fcppt::reference<sprite_sequence> const _sprites,
      bvh_tree_traits::tree_representation const &_tree,
      sge::image::color::rgba8 const &_color) const
  {
    if (!_tree.empty())
    {
      for (auto const &child : _tree)
      {
        this->add_children(_sprites, child, _color);
      }
    }
    else
    {
      for (auto const &elem :
           fcppt::variant::get_unsafe<bvh_tree_traits::leaf_wrapper_sequence>(_tree.value()))
      {
        _sprites.get().push_back(create_sprite(elem.value(), _color));
      }
    }
  }
};

FCPPT_RECORD_MAKE_LABEL(rectangle_count_label);

using arg_type = fcppt::record::object<fcppt::record::element<rectangle_count_label, unsigned>>;

awl::main::exit_code main_program(arg_type const &_args)
{
  unsigned const rectangle_count{fcppt::record::get<rectangle_count_label>(_args)};

  sge::window::dim const window_dim(
      1024U, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      1024U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  );

  sge::systems::instance<
      sge::systems::with_window,
      sge::systems::with_renderer<sge::systems::renderer_caps::ffp>,
      sge::systems::with_input> const
      sys(sge::systems::make_list(sge::systems::window(sge::systems::window_source(
          sge::systems::original_window(sge::window::title(FCPPT_TEXT("sge bvh example"))))))(
          sge::systems::renderer(
              sge::renderer::pixel_format::object(
                  sge::renderer::pixel_format::color::depth32,
                  sge::renderer::pixel_format::depth_stencil::off,
                  sge::renderer::pixel_format::optional_multi_samples(),
                  sge::renderer::pixel_format::srgb::no),
              sge::renderer::display_mode::parameters(
                  sge::renderer::display_mode::vsync::on,
                  sge::renderer::display_mode::optional_object()),
              sge::viewport::optional_resize_callback{sge::viewport::center_on_resize(
                  window_dim)}))(sge::systems::input(sge::systems::cursor_option_field::null())));

  sprite_buffers_type sprite_buffers(
      fcppt::make_ref(sys.renderer_device_core()), sge::sprite::buffers::option::dynamic);

  sprite_state_object sprite_state(
      fcppt::make_ref(sys.renderer_device_ffp()), sprite_state_parameters());

  using generator_type = fcppt::random::generator::minstd_rand;

  generator_type generator{fcppt::random::generator::seed_from_chrono<generator_type::seed>()};

  using real_distribution = fcppt::random::distribution::basic<
      fcppt::random::distribution::parameters::uniform_real<sge::renderer::scalar>>;

  using real_variate = fcppt::random::variate<generator_type, real_distribution>;

  real_variate screen_size_rng(
      fcppt::make_ref(generator),
      real_distribution(
          real_distribution::param_type::min(
              fcppt::cast::int_to_float<sge::renderer::scalar>(window_dim.h()) /
              fcppt::literal<sge::renderer::scalar>(
                  8 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  )),
          real_distribution::param_type::sup(
              fcppt::cast::int_to_float<sge::renderer::scalar>(window_dim.h()) -
              (fcppt::cast::int_to_float<sge::renderer::scalar>(window_dim.h()) /
                  fcppt::literal<sge::renderer::scalar>(
                      8 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                      )))));
  real_variate size_rng(
      fcppt::make_ref(generator),
      real_distribution(
          real_distribution::param_type::min(
              fcppt::cast::int_to_float<sge::renderer::scalar>(window_dim.h()) /
              fcppt::literal<sge::renderer::scalar>(
                  16 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  )),
          real_distribution::param_type::sup(
              fcppt::cast::int_to_float<sge::renderer::scalar>(window_dim.h()) /
              fcppt::literal<sge::renderer::scalar>(
                  4 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  ))));

  sge::bvh::object<bvh_tree_traits> bounding_hierarchy;

  bvh_tree_traits::leaf_sequence const nodes{fcppt::algorithm::map<bvh_tree_traits::leaf_sequence>(
      fcppt::make_int_range_count(rectangle_count),
      [&screen_size_rng, &size_rng](unsigned) -> bvh_box
      {
        bvh_box::dim const new_size(size_rng(), size_rng());

        return bvh_box{
            bvh_box::vector{screen_size_rng(), screen_size_rng()} -
                (new_size /
                 2.0F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                 )
                    .get_unsafe(),
            new_size};
      })};

  {
    using clock_type = std::chrono::steady_clock;

    clock_type::time_point const before{clock_type::now()};

    bounding_hierarchy.insert(nodes);

    std::cout
        << "Construction time: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(clock_type::now() - before).count()
        << '\n';
  }

  std::cout << "Resulting tree depth: "
            << fcppt::container::tree::depth(bounding_hierarchy.representation()) << '\n';

  bvh_traverser traverser{bounding_hierarchy.representation()};

  auto const draw(
      [&sprite_buffers, &sprite_state, &sys, &traverser]
      {
        sge::renderer::context::scoped_ffp const scoped_block(
            fcppt::make_ref(sys.renderer_device_ffp()),
            fcppt::reference_to_base<sge::renderer::target::base>(
                fcppt::make_ref(sys.renderer_device_ffp().onscreen_target())));

        scoped_block.get().clear(sge::renderer::clear::parameters().back_buffer(
            sge::image::color::any::object{sge::image::color::predef::black()}));

        sge::sprite::process::all(
            scoped_block.get(),
            sge::sprite::geometry::make_random_access_range(traverser.sprites()),
            sprite_buffers,
            sge::sprite::compare::default_(),
            sprite_state);
      });

  return sge::window::loop(
      sys.window_system(),
      sge::window::loop_function{
          [&sys, &draw, &traverser](awl::event::base const &_event)
          {
            sge::systems::quit_on_escape(sys, _event);

            fcppt::optional::maybe_void(
                fcppt::variant::dynamic_cast_<
                    fcppt::mpl::list::object<
                        sge::renderer::event::render const,
                        sge::input::keyboard::event::key const>,
                    fcppt::cast::dynamic_fun>(_event),
                [&draw, &traverser](auto const &_variant)
                {
                  fcppt::variant::match(
                      _variant,
                      [&draw](fcppt::reference<sge::renderer::event::render const>) { draw(); },
                      [&traverser](
                          fcppt::reference<sge::input::keyboard::event::key const> const _key_event)
                      { traverser.key_event(_key_event.get()); });
                });
          }});
}

}

awl::main::exit_code example_main(awl::main::function_context const &_function_context)
try
{
  fcppt::options::argument<rectangle_count_label, unsigned> const parser{
      fcppt::options::long_name{FCPPT_TEXT("rectangle-count")},
      fcppt::options::optional_help_text{}};

  using parser_type = decltype(parser);

  return fcppt::variant::match(
      fcppt::options::parse_help(
          fcppt::options::default_help_switch(),
          parser,
          fcppt::args_from_second(_function_context.argc(), _function_context.argv())),
      [](fcppt::options::result<fcppt::options::result_of<parser_type>> const &_result)
      {
        return fcppt::either::match(
            _result,
            [](fcppt::options::error const &_error) -> awl::main::exit_code
            {
              awl::show_error(fcppt::output_to_fcppt_string(_error));

              return awl::main::exit_failure();
            },
            [](fcppt::options::result_of<parser_type> const &_args) -> awl::main::exit_code
            { return main_program(fcppt::record::permute<arg_type>(_args)); });
      },
      [](fcppt::options::usage const &_usage)
      {
        awl::show_message(fcppt::output_to_fcppt_string(_usage));

        return awl::main::exit_success();
      });
}
catch (fcppt::exception const &_error)
{
  awl::show_error(_error.string());

  return awl::main::exit_failure();
}
catch (std::exception const &_error)
{
  awl::show_error_narrow(_error.what());

  return awl::main::exit_failure();
}
