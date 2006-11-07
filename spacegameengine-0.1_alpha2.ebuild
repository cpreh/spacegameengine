# Copyright 1999-2006 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

inherit games

DESCRIPTION="A portable easy to use engine written in C++"
HOMEPAGE="http://spacegameengine.sourceforge.net/"
SRC_URI="http://spacegameengine.sourceforge.net/${P}.tar.bz2"

LICENSE="GPL"
SLOT="0"
KEYWORDS="~x86 ~amd64"
IUSE="opengl truetype devil xinput"

DEPEND="${RDEPEND}
        scons"
RDEPEND="!games-engines/spacegame
         dev-libs/boost
         x11-libs/libX11
		 virtual/libc
		 media-fonts/corefonts
		 opengl? (
		 	media-libs/glew
			x11-libs/libXxf86vm )
         devil? ( media-libs/devil )
		 truetype? ( media-libs/freetype )
		 xinput? ( x11-libs/libXxf86dga )"

pkg_setup() {
	if !(use opengl && use truetype && use devil && use xinput) ; then
		eerror "For now you have to enable all useflags to get a working engine!\nPlease do: \"games-engines/spacegameengine opengl truetype devil xinput\" > /etc/portage/package.use"
		die
	fi
}

src_compile() {
	scons sandbox=${D} prefix=/usr libdir=$(get_libdir) flags="${CXXFLAGS}" || die
}

src_install() {
	scons install sandbox=${D} prefix=/usr libdir=$(get_libdir) || die
}
