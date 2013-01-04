#include "d3dx9.h"
#include "dds.h"
//--------------------------------------------------------------------------------------
#define ISBITMASK( r,g,b,a ) ( ddpf.dwRBitMask == r && ddpf.dwGBitMask == g && ddpf.dwBBitMask == b && ddpf.dwABitMask == a )

D3DFORMAT GetD3D9Format( const DDS_PIXELFORMAT& ddpf );
    