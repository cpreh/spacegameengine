#include "../file.hpp"
#include "../load_context.hpp"
#include "../write_context.hpp"
#include <sge/math/dim/basic_impl.hpp>
#include <sge/optional_impl.hpp>
#include <sge/image/view/dim.hpp>
#include <sge/image/view/format.hpp>
#include <sge/image/view/make.hpp>
#include <sge/image/algorithm/copy_and_convert.hpp>
#include <sge/image/color/format_stride.hpp>

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

sge::libpng::file::file(
	image::view::const_object const &_view)
{
	data(
		_view);
}

void sge::libpng::file::data(
	image::view::const_object const &_view)
{
	dim_ = 
		image::view::dim(
			_view);

	format_ = 
		image::view::format(
			_view);
	
	bytes_.resize(
		dim_.content() * 
		image::color::format_stride(
			format_));

	image::algorithm::copy_and_convert(
		_view,
		image::view::make(
			bytes_.data(),
			dim_,
			format_,
			image::view::optional_pitch()));
}

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

void sge::libpng::file::save(
	filesystem::path const &p)
{
	write_context context(
		p,
		dim(),
		bytes_,
		format_);
}
