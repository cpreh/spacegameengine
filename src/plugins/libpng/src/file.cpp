#include "../file.hpp"
#include "../load_context.hpp"
#include <sge/image/view/make.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/optional_impl.hpp>

sge::libpng::file::file(
	sge::filesystem::path const &_path)
{
	load_context context(
		_path);
	dim_ = context.dim();
	bytes_.swap(
		context.bytes());
	format_ = context.format();
}

void sge::libpng::file::data(
	image::view::const_object const &) {}

sge::image::view::const_object const sge::libpng::file::view() const
{
	return 
		image::view::make(
			reinterpret_cast<image::const_raw_pointer>(
				bytes_.data()),
			dim(),
			format_,
			image::view::optional_pitch());
}

sge::image::dim_type const sge::libpng::file::dim() const
{
	return dim_;
}

void sge::libpng::file::resample(
	image::dim_type const &) {}

void sge::libpng::file::save(
	filesystem::path const &) {}
