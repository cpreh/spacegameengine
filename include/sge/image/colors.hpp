/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_IMAGE_COLORS_HPP_INCLUDED
#define SGE_IMAGE_COLORS_HPP_INCLUDED

#include <sge/image/color/any/object.hpp>
#include <sge/symbol.hpp>

namespace sge
{
namespace image
{

#define SGE_DECLARE_COLOR(name)\
SGE_SYMBOL color::any::object const name();

namespace colors {
	SGE_DECLARE_COLOR(aliceblue            )
	SGE_DECLARE_COLOR(antiquewhite         )
	SGE_DECLARE_COLOR(aqua                 )
	SGE_DECLARE_COLOR(aquamarine           )
	SGE_DECLARE_COLOR(azure                )
	SGE_DECLARE_COLOR(beige                )
	SGE_DECLARE_COLOR(bisque               )
	SGE_DECLARE_COLOR(black                )
	SGE_DECLARE_COLOR(blanchedalmond       )
	SGE_DECLARE_COLOR(blue                 )
	SGE_DECLARE_COLOR(blueviolet           )
	SGE_DECLARE_COLOR(brown                )
	SGE_DECLARE_COLOR(burlywood            )
	SGE_DECLARE_COLOR(cadetblue            )
	SGE_DECLARE_COLOR(chartreuse           )
	SGE_DECLARE_COLOR(chocolate            )
	SGE_DECLARE_COLOR(coral                )
	SGE_DECLARE_COLOR(cornflowerblue       )
	SGE_DECLARE_COLOR(cornsilk             )
	SGE_DECLARE_COLOR(crimson              )
	SGE_DECLARE_COLOR(cyan                 )
	SGE_DECLARE_COLOR(darkblue             )
	SGE_DECLARE_COLOR(darkcyan             )
	SGE_DECLARE_COLOR(darkgoldenrod        )
	SGE_DECLARE_COLOR(darkgray             )
	SGE_DECLARE_COLOR(darkgreen            )
	SGE_DECLARE_COLOR(darkgrey             )
	SGE_DECLARE_COLOR(darkkhaki            )
	SGE_DECLARE_COLOR(darkmagenta          )
	SGE_DECLARE_COLOR(darkolivegreen       )
	SGE_DECLARE_COLOR(darkorange           )
	SGE_DECLARE_COLOR(darkorchid           )
	SGE_DECLARE_COLOR(darkred              )
	SGE_DECLARE_COLOR(darksalmon           )
	SGE_DECLARE_COLOR(darkseagreen         )
	SGE_DECLARE_COLOR(darkslateblue        )
	SGE_DECLARE_COLOR(darkslategray        )
	SGE_DECLARE_COLOR(darkslategrey        )
	SGE_DECLARE_COLOR(darkturquoise        )
	SGE_DECLARE_COLOR(darkviolet           )
	SGE_DECLARE_COLOR(deeppink             )
	SGE_DECLARE_COLOR(deepskyblue          )
	SGE_DECLARE_COLOR(dimgray              )
	SGE_DECLARE_COLOR(dimgrey              )
	SGE_DECLARE_COLOR(dodgerblue           )
	SGE_DECLARE_COLOR(firebrick            )
	SGE_DECLARE_COLOR(floralwhite          )
	SGE_DECLARE_COLOR(forestgreen          )
	SGE_DECLARE_COLOR(fuchsia              )
	SGE_DECLARE_COLOR(gainsboro            )
	SGE_DECLARE_COLOR(ghostwhite           )
	SGE_DECLARE_COLOR(gold                 )
	SGE_DECLARE_COLOR(goldenrod            )
	SGE_DECLARE_COLOR(gray                 )
	SGE_DECLARE_COLOR(green                )
	SGE_DECLARE_COLOR(greenyellow          )
	SGE_DECLARE_COLOR(grey                 )
	SGE_DECLARE_COLOR(honeydew             )
	SGE_DECLARE_COLOR(hotpink              )
	SGE_DECLARE_COLOR(indianred            )
	SGE_DECLARE_COLOR(indigo               )
	SGE_DECLARE_COLOR(ivory                )
	SGE_DECLARE_COLOR(khaki                )
	SGE_DECLARE_COLOR(lavender             )
	SGE_DECLARE_COLOR(lavenderblush        )
	SGE_DECLARE_COLOR(lawngreen            )
	SGE_DECLARE_COLOR(lemonchiffon         )
	SGE_DECLARE_COLOR(lightblue            )
	SGE_DECLARE_COLOR(lightcoral           )
	SGE_DECLARE_COLOR(lightcyan            )
	SGE_DECLARE_COLOR(lightgoldenrodyellow )
	SGE_DECLARE_COLOR(lightgray            )
	SGE_DECLARE_COLOR(lightgreen           )
	SGE_DECLARE_COLOR(lightgrey            )
	SGE_DECLARE_COLOR(lightpink            )
	SGE_DECLARE_COLOR(lightsalmon          )
	SGE_DECLARE_COLOR(lightseagreen        )
	SGE_DECLARE_COLOR(lightskyblue         )
	SGE_DECLARE_COLOR(lightslategray       )
	SGE_DECLARE_COLOR(lightslategrey       )
	SGE_DECLARE_COLOR(lightsteelblue       )
	SGE_DECLARE_COLOR(lightyellow          )
	SGE_DECLARE_COLOR(lime                 )
	SGE_DECLARE_COLOR(limegreen            )
	SGE_DECLARE_COLOR(linen                )
	SGE_DECLARE_COLOR(magenta              )
	SGE_DECLARE_COLOR(maroon               )
	SGE_DECLARE_COLOR(mediumaquamarine     )
	SGE_DECLARE_COLOR(mediumblue           )
	SGE_DECLARE_COLOR(mediumorchid         )
	SGE_DECLARE_COLOR(mediumpurple         )
	SGE_DECLARE_COLOR(mediumseagreen       )
	SGE_DECLARE_COLOR(mediumslateblue      )
	SGE_DECLARE_COLOR(mediumspringgreen    )
	SGE_DECLARE_COLOR(mediumturquoise      )
	SGE_DECLARE_COLOR(mediumvioletred      )
	SGE_DECLARE_COLOR(midnightblue         )
	SGE_DECLARE_COLOR(mintcream            )
	SGE_DECLARE_COLOR(mistyrose            )
	SGE_DECLARE_COLOR(moccasin             )
	SGE_DECLARE_COLOR(navajowhite          )
	SGE_DECLARE_COLOR(navy                 )
	SGE_DECLARE_COLOR(oldlace              )
	SGE_DECLARE_COLOR(olive                )
	SGE_DECLARE_COLOR(olivedrab            )
	SGE_DECLARE_COLOR(orange               )
	SGE_DECLARE_COLOR(orangered            )
	SGE_DECLARE_COLOR(orchid               )
	SGE_DECLARE_COLOR(palegoldenrod        )
	SGE_DECLARE_COLOR(palegreen            )
	SGE_DECLARE_COLOR(paleturquoise        )
	SGE_DECLARE_COLOR(palevioletred        )
	SGE_DECLARE_COLOR(papayawhip           )
	SGE_DECLARE_COLOR(peachpuff            )
	SGE_DECLARE_COLOR(peru                 )
	SGE_DECLARE_COLOR(pink                 )
	SGE_DECLARE_COLOR(plum                 )
	SGE_DECLARE_COLOR(powderblue           )
	SGE_DECLARE_COLOR(purple               )
	SGE_DECLARE_COLOR(red                  )
	SGE_DECLARE_COLOR(rosybrown            )
	SGE_DECLARE_COLOR(royalblue            )
	SGE_DECLARE_COLOR(saplebrown           )
	SGE_DECLARE_COLOR(salmon               )
	SGE_DECLARE_COLOR(sandybrown           )
	SGE_DECLARE_COLOR(seagreen             )
	SGE_DECLARE_COLOR(seashell             )
	SGE_DECLARE_COLOR(sienna               )
	SGE_DECLARE_COLOR(silver               )
	SGE_DECLARE_COLOR(skyblue              )
	SGE_DECLARE_COLOR(slateblue            )
	SGE_DECLARE_COLOR(slategray            )
	SGE_DECLARE_COLOR(slategrey            )
	SGE_DECLARE_COLOR(snow                 )
	SGE_DECLARE_COLOR(springgreen          )
	SGE_DECLARE_COLOR(steelblue            )
	SGE_DECLARE_COLOR(tan                  )
	SGE_DECLARE_COLOR(teal                 )
	SGE_DECLARE_COLOR(thistle              )
	SGE_DECLARE_COLOR(tomato               )
	SGE_DECLARE_COLOR(turquoise            )
	SGE_DECLARE_COLOR(violet               )
	SGE_DECLARE_COLOR(wheat                )
	SGE_DECLARE_COLOR(white                )
	SGE_DECLARE_COLOR(whitesmoke           )
	SGE_DECLARE_COLOR(yellow               )
	SGE_DECLARE_COLOR(yellowgreen          )
	SGE_DECLARE_COLOR(transparent          )
}

}
}

#undef SGE_DELCARE_COLOR

#endif
