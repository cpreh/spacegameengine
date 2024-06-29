//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/charconv/utf8_string.hpp>
#include <sge/image/color/rgb32f.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <sge/log/location.hpp>
#include <sge/model/obj/exception.hpp>
#include <sge/model/obj/identifier.hpp>
#include <sge/model/obj/material_map.hpp>
#include <sge/model/obj/parse_mtllib.hpp>
#include <sge/model/obj/impl/log_name.hpp>
#include <sge/model/obj/material/ambient_color.hpp>
#include <sge/model/obj/material/diffuse_color.hpp>
#include <sge/model/obj/material/diffuse_texture_path.hpp>
#include <sge/model/obj/material/emissive_color.hpp>
#include <sge/model/obj/material/object.hpp>
#include <sge/model/obj/material/shininess.hpp>
#include <sge/model/obj/material/specular_color.hpp>
#include <sge/model/obj/material/specular_texture_path.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vector3.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_impl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/math/vector/output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace
{

// TODO(philipp): Refactor this
class parser
{
  FCPPT_NONMOVABLE(parser);

public:
  parser(fcppt::log::context_reference const _log_context, std::filesystem::path const &_filename)
      : log_{_log_context, sge::log::location(), sge::model::obj::impl::log_name()},
        parent_path_(_filename.parent_path()),
        result_(),
        current_line_(0U),
        current_material_(sge::charconv::utf8_string{}),
        shininess_(),
        ambient_(),
        diffuse_(),
        specular_(),
        emissive_(),
        diffuse_texture_(),
        specular_texture_()
  {
    std::ifstream stream(_filename);

    if (!stream.is_open())
    {
      throw sge::model::obj::exception(
          FCPPT_TEXT("Couldn't open file \"") + fcppt::filesystem::path_to_string(_filename) +
          FCPPT_TEXT("\""));
    }

    std::string line;

    while (std::getline(stream, line))
    {
      ++current_line_;

      if (line.empty() || line[0] == '#')
      {
        continue;
      }

      std::string::size_type const first_space_position = line.find(' ');

      this->throw_error_if(
          first_space_position == std::string::npos, FCPPT_TEXT("No prefix found"));

      prefix_type const prefix{line.substr(0, first_space_position)};

      rest_of_line_type const rest_of_line{line.substr(first_space_position + 1U)};

      this->parse_line(prefix, rest_of_line);
    }

    this->push_material();
  }

  ~parser() = default;

  [[nodiscard]] sge::model::obj::material_map const &result() const { return result_; }

  void throw_error_if(bool const _condition, fcppt::string const &_error_message) const
  {
    if (_condition)
    {
      throw sge::model::obj::exception(
          FCPPT_TEXT("Error on line ") + fcppt::output_to_fcppt_string(current_line_) +
          FCPPT_TEXT(": ") + _error_message);
    }
  }

  FCPPT_DECLARE_STRONG_TYPEDEF(std::string, prefix_type);
  FCPPT_DECLARE_STRONG_TYPEDEF(std::string, rest_of_line_type);

  void parse_line(prefix_type const &_prefix, rest_of_line_type const &_rest_of_line)
  {
    if (_prefix.get() == "Ns")
    {
      std::istringstream ss{_rest_of_line.get()};

      sge::renderer::scalar new_shininess; // NOLINT(cppcoreguidelines-init-variables)

      this->throw_error_if(!(ss >> new_shininess), FCPPT_TEXT("Invalid shininess."));

      shininess_ = optional_shininess(new_shininess);
    }
    else if (_prefix.get() == "Ka")
    {
      std::istringstream ss{_rest_of_line.get()};

      sge::renderer::vector3 new_ambient{fcppt::no_init()};

      this->throw_error_if(
          !(ss >> new_ambient.x() >> new_ambient.y() >> new_ambient.z()),
          FCPPT_TEXT("Invalid ambient"));

      ambient_ = optional_color(new_ambient);
    }
    else if (_prefix.get() == "Ke")
    {
      std::istringstream ss{_rest_of_line.get()};

      sge::renderer::scalar new_emissive; // NOLINT(cppcoreguidelines-init-variables)

      this->throw_error_if(!(ss >> new_emissive), FCPPT_TEXT("Invalid emissive"));

      emissive_ = optional_color(sge::renderer::vector3(new_emissive, new_emissive, new_emissive));
    }
    else if (_prefix.get() == "Kd")
    {
      std::istringstream ss{_rest_of_line.get()};

      sge::renderer::vector3 new_diffuse{fcppt::no_init()};

      this->throw_error_if(
          !(ss >> new_diffuse.x() >> new_diffuse.y() >> new_diffuse.z()),
          FCPPT_TEXT("Invalid diffuse"));

      diffuse_ = optional_color(new_diffuse);
    }
    else if (_prefix.get() == "Ks")
    {
      std::istringstream ss{_rest_of_line.get()};

      sge::renderer::vector3 new_specular{fcppt::no_init()};

      this->throw_error_if(
          !(ss >> new_specular.x() >> new_specular.y() >> new_specular.z()),
          FCPPT_TEXT("Invalid specular"));

      specular_ = optional_color(new_specular);
    }
    else if (_prefix.get() == "Ni")
    {
      // Not usable
    }
    else if (_prefix.get() == "d")
    {
      std::istringstream ss{_rest_of_line.get()};

      sge::renderer::scalar dissolve; // NOLINT(cppcoreguidelines-init-variables)

      this->throw_error_if(!(ss >> dissolve), FCPPT_TEXT("Invalid dissolve"));

      FCPPT_LOG_WARNING(
          log_, fcppt::log::out << FCPPT_TEXT("obj (mtl): dissolve currently not supported"))
      /*
			(*diffuse_)[3] =
				dissolve;
			if(std::abs(dissolve - 1.0f) > 0.0001f)
				throw
					sge::model::obj::exception(
						FCPPT_TEXT("Error on line ")+
						fcppt::output_to_fcppt_string(
							current_line_)+
						FCPPT_TEXT(": Invalid dissolve value (!= 1, not supported)."));
			*/
    }
    else if (_prefix.get() == "illum")
    {
      std::istringstream ss{_rest_of_line.get()};

      unsigned light_model; // NOLINT(cppcoreguidelines-init-variables)

      this->throw_error_if(!(ss >> light_model), FCPPT_TEXT("Invalid light model"));

      switch (light_model)
      {
      case 0U:
        ambient_ = optional_color(fcppt::math::vector::null<sge::renderer::vector3>());
        break;
      case 1U:
        specular_ = optional_color(fcppt::math::vector::null<sge::renderer::vector3>());
        break;
      case 2U:
        break;
      default:
        FCPPT_LOG_WARNING(
            log_, fcppt::log::out << FCPPT_TEXT("obj (mtl): invalid light model: ") << light_model)
        break;
      }
    }
    else if (_prefix.get() == "map_Kd")
    {
      diffuse_texture_ = optional_path(parent_path_ / std::filesystem::path(_rest_of_line.get()));
    }
    else if (_prefix.get() == "map_Ks")
    {
      specular_texture_ = optional_path(parent_path_ / std::filesystem::path(_rest_of_line.get()));
    }
    else if (_prefix.get() == "newmtl")
    {
      // First material we see? Do nothing.
      if (!current_material_.get().empty())
      {
        this->push_material();
      }

      current_material_ = sge::model::obj::identifier(
          sge::charconv::utf8_string(_rest_of_line.get().begin(), _rest_of_line.get().end()));
    }
    else
    {
      FCPPT_LOG_WARNING(log_, fcppt::log::out << FCPPT_TEXT("obj (mtl): invalid prefix"))
    }
  }

  void push_material()
  {
    auto const make_exception(
        [this]
        {
          return sge::model::obj::exception{
              FCPPT_TEXT("Error on line ") + fcppt::output_to_fcppt_string(current_line_) +
              FCPPT_TEXT(": Material without ambient/specular/emissive/diffuse/shininess.")};
        });

    auto const make_color(
        [](sge::renderer::vector3 const &_vec)
        {
          return sge::image::color::any::object{
              sge::image::color::rgb32f{(sge::image::color::init::red() %= (_vec).x())(
                  sge::image::color::init::green() %=
                  (_vec).y())(sge::image::color::init::blue() %= (_vec).z())}};
        });

    result_.insert(std::make_pair(
        current_material_,
        sge::model::obj::material::object(
            sge::model::obj::identifier{current_material_},
            sge::model::obj::material::diffuse_color(
                make_color(fcppt::optional::to_exception(diffuse_, make_exception))),
            sge::model::obj::material::ambient_color(
                make_color(fcppt::optional::to_exception(ambient_, make_exception))),
            sge::model::obj::material::specular_color(
                make_color(fcppt::optional::to_exception(specular_, make_exception))),
            sge::model::obj::material::emissive_color(
                make_color(fcppt::optional::to_exception(emissive_, make_exception))),
            sge::model::obj::material::shininess(
                fcppt::optional::to_exception(shininess_, make_exception)),
            sge::model::obj::material::diffuse_texture_path(
                fcppt::optional::from(diffuse_texture_, [] { return std::filesystem::path(); })),
            sge::model::obj::material::specular_texture_path(fcppt::optional::from(
                specular_texture_, [] { return std::filesystem::path(); })))));
  }

private:
  fcppt::log::object log_;

  std::filesystem::path const parent_path_;

  sge::model::obj::material_map result_;

  unsigned current_line_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)

  sge::model::obj::identifier current_material_;

  using optional_shininess = fcppt::optional::object<sge::renderer::scalar>;

  optional_shininess shininess_;

  using optional_color = fcppt::optional::object<sge::renderer::vector3>;

  optional_color ambient_;

  optional_color diffuse_;

  optional_color specular_;

  optional_color emissive_;

  using optional_path = fcppt::optional::object<std::filesystem::path>;

  optional_path diffuse_texture_;

  optional_path specular_texture_;
};

}

sge::model::obj::material_map sge::model::obj::parse_mtllib(
    fcppt::log::context_reference const _log_context, std::filesystem::path const &_filename)
{
  parser const p{_log_context, _filename};

  return p.result();
}
