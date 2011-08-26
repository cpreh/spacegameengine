#!/bin/sh
pushd include > /dev/null
convenience_headers sge || exit -1

# remove opengl from renderer
sed -i 's@#include <sge/renderer/opengl/opengl.hpp>$@@' sge/renderer/renderer.hpp
popd > /dev/null

multi_update_license util/license_paths.json
