#ifndef SGE_LIBPNG_FILE_HPP_INCLUDED
#define SGE_LIBPNG_FILE_HPP_INCLUDED

#include "byte_vector.hpp"
#include <sge/image/color/format.hpp>
#include <sge/image/file.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/math/dim/basic_decl.hpp>

namespace sge
{
namespace libpng
{
class file
:
	public image::file
{
public:
	explicit file(
		fcppt::filesystem::path const &
	);

	explicit file(
		image::view::const_object const &
	);

	void data(
		image::view::const_object const &);
	image::view::const_object const view() const;
	image::dim_type const dim() const;
	void save(
		fcppt::filesystem::path const &);
private:
	image::dim_type dim_;
	byte_vector bytes_;
	image::color::format::type format_;
};
}
}

#endif
