// SPDX-License-Identifier: MIT
// iRL: offline definitions of the iOS runtime hooks that FEXCore references when built with
// FEX_IOS_HOST. At runtime they live in the ARM64EC module (Module.cpp, IosJitAlias.cpp,
// IosMonoBridge.cpp), which FEXOfflineCompiler doesn't link.
//
// Each stub matches the runtime's answer for every image the AOT pipeline compiles:
//  - subfloor windows exist only for images with a preferred base below 4 GB, which
//    tools/aot/gen_codemaps.py excludes, so "no window / identity" is the runtime's answer too;
//  - the Mono bridge and the JIT alias table are only populated for runtime-generated guest code
//    (never for PE images on disk), so "miss / identity" is exact;
//  - DualMap::WriteOffset = 0: the offline compiler writes code into its own RW buffer;
//  - diagnostics (branch trace, FFS-bypass log) are off.
#include <cstdint>

namespace FEXCore {
namespace Core {
  uint32_t IosGuestBranchTraceEnabled = 0;
}
namespace DualMap {
  int64_t WriteOffset = 0;
}
} // namespace FEXCore

extern "C" {
uint64_t IosFfsBypassLog[4] {};
uint64_t IosSubfloorToReal(uint64_t Addr) { return Addr; }
int IosSubfloorWindowForCode(uint64_t, uint64_t*, uint64_t*, uint64_t*) { return 0; }
int IosSubfloorEnum(int, uint64_t*, uint64_t*, uint64_t*) { return 0; }
uint64_t IosJitReverseTranslate(uint64_t Addr) { return Addr; }
uint64_t IosMonoResolveRW(uint64_t, uint64_t) { return 0; }
void ios_fex_mono_arm(uint64_t, uint64_t) {}
int ios_fex_mono_bridge_armed() { return 0; }
uint64_t ios_fex_mono_captured_count() { return 0; }
void ios_fex_mono_count_activated() {}
void ios_fex_mono_count_helper(int) {}
int ios_fex_mono_take_pending(uint64_t*, uint64_t*, uint64_t*) { return 0; }
}
