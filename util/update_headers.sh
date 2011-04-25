#!/bin/sh
pushd include > /dev/null
convenience_headers sge || exit -1
popd > /dev/null
multi_update_license util/license_paths.json
