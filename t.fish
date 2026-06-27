#!/usr/bin/env fish

set -l files (fd -e vcxproj -e props -e targets)

for file in $files
    sed -i \
        -e 's|\$(xrBinRootDir)|./../_build/bin/|g' \
        -e 's|\$(xrBinPlugRootDir)|./../_build/bin_plugs/|g' \
        -e 's|\$(xrLibRootDir)|./../_build/lib/|g' \
        -e 's|\$(xrBinDir)|./../_build/bin/$(Configuration)/|g' \
        -e 's|\$(xrBinPlugDir)|./../_build/bin_plugs/$(Configuration)/|g' \
        -e 's|\$(xrLibDir)|./../_build/lib/$(Configuration)/|g' \
        -e 's|\$(xrIntDir)|./../_build/intermediate/$(Configuration)/|g' \
        -e 's|\$(xrSdkDir)|./../sdk/|g' \
        -e 's|\$(xrGameDir)|./../_build/_game/|g' \
        -e 's|\$(xrGameBinDir)|./../_build/_game/bin/|g' \
        -e 's|\$(xr3rdPartyDir)|./3rd party/|g' \
        -e 's|\$(dxSdkDir)|./../sdk/include/dxsdk/|g' \
        "$file"
end
