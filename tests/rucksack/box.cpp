/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/axis_policy2_comparison.hpp>
#include <sge/rucksack/axis_policy2_output.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/padding.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/box.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <sge/rucksack/widget/reference.hpp>
#include <sge/rucksack/widget/reference_alignment.hpp>
#include <sge/rucksack/widget/reference_alignment_container.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <fcppt/config/external_end.hpp>


TEST_CASE(
	"rucksack::box",
	"[sge]"
)
{
	sge::rucksack::widget::dummy child1{
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::minimum_size{
					0
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					10
				}
			}
		}
	};

	sge::rucksack::widget::box box1{
		sge::rucksack::axis::x,
		sge::rucksack::padding{
			0
		},
		sge::rucksack::widget::reference_alignment_container{
			sge::rucksack::widget::reference_alignment{
				sge::rucksack::widget::reference{
					child1
				},
				sge::rucksack::alignment::center
			}
		}
	};

	box1.size(
		sge::rucksack::dim{
			100,
			100
		}
	);

	CHECK(
		box1.axis_policy()
		==
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::minimum_size{
					0
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					10
				}
			}
		}
	);

	box1.relayout();

	CHECK(
		child1.size()
		==
		sge::rucksack::dim{
			100,
			10
		}
	);

	sge::rucksack::widget::dummy child2{
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					10
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					10
				}
			}
		}
	};

	box1.push_back_child(
		child2,
		sge::rucksack::alignment::center
	);

	box1.relayout();

	CHECK(
		box1.axis_policy()
		==
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::minimum_size{
					10
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					10
				}
			}
		}
	);

	CHECK(
		child1.size()
		==
		sge::rucksack::dim{
			90,
			10
		}
	);

	CHECK(
		child2.size()
		==
		sge::rucksack::dim{
			10,
			10
		}
	);
}

TEST_CASE(
	"rucksack::box in box",
	"[sge]"
)
{
	sge::rucksack::widget::dummy child_x_1{
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::minimum_size{
					0
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					10
				}
			}
		}
	};

	sge::rucksack::widget::dummy child_x_2{
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					20
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					20
				}
			}
		}
	};

	sge::rucksack::widget::box box1{
		sge::rucksack::axis::x,
		sge::rucksack::padding{
			0
		},
		sge::rucksack::widget::reference_alignment_container{
			sge::rucksack::widget::reference_alignment{
				sge::rucksack::widget::reference{
					child_x_1
				},
				sge::rucksack::alignment::center
			},
			sge::rucksack::widget::reference_alignment{
				sge::rucksack::widget::reference{
					child_x_2
				},
				sge::rucksack::alignment::left_or_top
			}
		}
	};

	sge::rucksack::widget::dummy child_y_1{
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::minimum_size{
					0
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					10
				}
			}
		}
	};

	sge::rucksack::widget::dummy child_y_2{
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::minimum_size{
					0
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					0
				}
			}
		}
	};

	sge::rucksack::widget::box box2{
		sge::rucksack::axis::y,
		sge::rucksack::padding{
			0
		},
		sge::rucksack::widget::reference_alignment_container{
			sge::rucksack::widget::reference_alignment{
				sge::rucksack::widget::reference{
					box1
				},
				sge::rucksack::alignment::center
			},
			sge::rucksack::widget::reference_alignment{
				sge::rucksack::widget::reference{
					child_y_1
				},
				sge::rucksack::alignment::center
			},
			sge::rucksack::widget::reference_alignment{
				sge::rucksack::widget::reference{
					child_y_2
				},
				sge::rucksack::alignment::center
			}
		}
	};

	box2.size(
		sge::rucksack::dim{
			100,
			30
		}
	);

	CHECK(
		box2.axis_policy()
		==
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::minimum_size{
					20
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					30
				}
			}
		}
	);

	box2.relayout();

	CHECK(
		child_x_1.position()
		==
		sge::rucksack::vector{
			0,
			5
		}
	);

	CHECK(
		child_x_2.position()
		==
		sge::rucksack::vector{
			80,
			0
		}
	);

	CHECK(
		child_x_1.size()
		==
		sge::rucksack::dim{
			80,
			10
		}
	);

	CHECK(
		child_x_2.size()
		==
		sge::rucksack::dim{
			20,
			20
		}
	);

	CHECK(
		box1.size()
		==
		sge::rucksack::dim{
			100,
			20
		}
	);

	CHECK(
		child_y_1.size()
		==
		sge::rucksack::dim{
			100,
			10
		}
	);

	box1.pop_back_child();

	box1.relayout();

	CHECK(
		box1.position()
		==
		sge::rucksack::vector{
			0,
			0
		}
	);

	box1.push_back_child(
		child_x_2,
		sge::rucksack::alignment::left_or_top
	);

	box1.relayout();

	CHECK(
		box1.position()
		==
		sge::rucksack::vector{
			0,
			0
		}
	);
}
