//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_UNSUPPORTED_HPP_INCLUDED
#define SGE_RENDERER_UNSUPPORTED_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <fcppt/string.hpp>

namespace sge::renderer
{

/**
\brief An exception that is thrown when unsupported features are used

\ingroup sge_renderer
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL unsupported : public sge::renderer::exception
{
public:
  // TODO(philipp): strong typedefs
  SGE_RENDERER_DETAIL_SYMBOL
  unsupported(
      fcppt::string const &feature,
      fcppt::string const &minimum_version_required,
      fcppt::string const &possible_extensions);

  /**
	\brief Returns the name of the missing feature
	*/
  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL fcppt::string const &feature() const;

  /**
	\brief Returns the minimum version that is required to get the feature
	*/
  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL fcppt::string const &minimum_version_required() const;

  /**
	\brief Returns possible extensions that could provide the feature
	*/
  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL fcppt::string const &possible_extensions() const;

  SGE_RENDERER_DETAIL_SYMBOL
  unsupported(unsupported &&) noexcept;

  SGE_RENDERER_DETAIL_SYMBOL
  unsupported(unsupported const &);

  SGE_RENDERER_DETAIL_SYMBOL
  unsupported &operator=(unsupported &&) noexcept;

  SGE_RENDERER_DETAIL_SYMBOL
  unsupported &operator=(unsupported const &);

  SGE_RENDERER_DETAIL_SYMBOL
  ~unsupported() noexcept override;

private:
  fcppt::string feature_, minimum_version_required_, possible_extensions_;
};

}

#endif
