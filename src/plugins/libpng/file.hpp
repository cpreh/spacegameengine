#ifndef SGE_LIBPNG_FILE_HPP_INCLUDED
#define SGE_LIBPNG_FILE_HPP_INCLUDED

#include "byte_vector.hpp"
#include <sge/image/color/format.hpp>
#include <sge/math/dim/basic_decl.hpp>
#include <sge/image/file.hpp>

namespace sge
{
namespace libpng
{
class file
:
	public image::file
{
public:
	file(
		sge::filesystem::path const &);
	void data(
		image::view::const_object const &);
	image::view::const_object const view() const;
	image::dim_type const dim() const;
	void resample(
		image::dim_type const &);
	void save(
		filesystem::path const &);
private:
	image::dim_type dim_;
	byte_vector bytes_;
	image::color::format::type format_;
};
}
}

#endif
