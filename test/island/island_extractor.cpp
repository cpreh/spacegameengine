#include "../../src/math/utility.hpp"
#include "island_extractor.hpp"

island_extractor::island_extractor() {}
island_extractor::island_extractor(island_extractor::field_type &image) { reset(image); }

void island_extractor::reset(island_extractor::field_type &_image)
{
	image = _image;

	// Randinseln fluten
	for (coord_type x = 0; x < image.width(); ++x)
	{
		if (!sge::math::almost_zero(image.pos(x,0)))
			fast_fill(x,0);
		if (!sge::math::almost_zero(image.pos(x,image.height()-1)))
			fast_fill(x,image.height()-1);
	}

	for (coord_type y = 0; y < image.height(); ++y)
	{
		if (!sge::math::almost_zero(image.pos(0,y)))
			fast_fill(0,y);
		if (!sge::math::almost_zero(image.pos(image.width()-1,y)))
			fast_fill(image.width()-1,y);
	}
}

void island_extractor::fast_fill(const island_extractor::coord_type &x,const island_extractor::coord_type &y)
{
	field_type::value_type &c = image.pos(x,y);

	if (sge::math::almost_zero(c))
		return;

	c = 0;

	if (x != 0)
	{
		fast_fill(x-1,y);
		if (y != 0)
			fast_fill(x-1,y-1);
		if (y < image.height()-1)
			fast_fill(x-1,y+1);
	}

	if (x < image.width()-1)
	{
		fast_fill(x+1,y);
		if (y != 0)
			fast_fill(x+1,y-1);
		if (y < image.height()-1)
			fast_fill(x+1,y+1);
	}

	if (y < image.height()-1)
		fast_fill(x,y+1);
	if (y != 0)
		fast_fill(x,y-1);
}

void island_extractor::flood_fill(const island_extractor::coord_type &x,const island_extractor::coord_type &y,island_extractor::pixel_list_type &pixel_list)
{
	field_type::value_type &c = image.pos(x,y);

	if (sge::math::almost_zero(c))
		return;

	pixel_list.push_back(pos_type(x,y));
	c = 0;

	if (x != 0)
	{
		flood_fill(x-1,y,pixel_list);
		if (y != 0)
			flood_fill(x-1,y-1,pixel_list);
		if (y < image.height()-1)
			flood_fill(x-1,y+1,pixel_list);
	}

	if (x < image.width()-1)
	{
		flood_fill(x+1,y,pixel_list);
		if (y != 0)
			flood_fill(x+1,y-1,pixel_list);
		if (y < image.height()-1)
			flood_fill(x+1,y+1,pixel_list);
	}

	if (y < image.height()-1)
		flood_fill(x,y+1,pixel_list);
	if (y != 0)
		flood_fill(x,y-1,pixel_list);
}

island_extractor::rect_type island_extractor::bounding_rect(const island_extractor::pixel_list_type &pixel_list) const
{
	rect_type b(pixel_list.front().x(),pixel_list.front().y(),pixel_list.front().x(),pixel_list.front().y());
	for (pixel_list_type::const_iterator i = pixel_list.begin(); i != pixel_list.end(); ++i)
	{
		if (i->x() < b.left)
			b.left = i->x();
		if (i->x() > b.right)
			b.right = i->x();
		if (i->y() < b.top)
			b.top = i->y();
		if (i->y() > b.bottom)
			b.bottom = i->y();
	}
	return rect_type(b.left,b.top,b.right+1,b.bottom+1);
}

void island_extractor::extract_list(island_extractor::field_list_type &fields)
{
	field_type n;
	while (extract(n))
		fields.push_back(n);
}

bool island_extractor::extract(island_extractor::field_type &target)
{
	pixel_list_type pixel_list;

	while (pixel_list.size() < pixel_list_type::size_type(50))
	{
		pixel_list.clear();

		for (field_type::iterator i = image.begin(); i != image.end(); ++i)
		{
			if (!sge::math::almost_zero(*i))
			{
				flood_fill((i-image.begin())%image.width(),(i-image.begin())/image.width(),pixel_list);
				break;
			}
		}

		if (pixel_list.size() == 0)
			break;
	}

	// Keine Insel (mehr) gefunden? :(
	if (pixel_list.size() == 0)
		return false;

	// Bounding-Rect bestimmen
	const rect_type r = bounding_rect(pixel_list);

	// Und in einzelnes Bild umwandeln
	target = field_type(field_type::dim_type(r.width(),r.height()));
	target.zero();

	const pos_type lefttop = pos_type(r.left,r.top);
	// Koordinaten "normieren" und in Bild schreiben
	for (pixel_list_type::iterator i = pixel_list.begin(); i != pixel_list.end(); ++i)
		target.pos((*i - lefttop)) = 1;

	return true;
}
