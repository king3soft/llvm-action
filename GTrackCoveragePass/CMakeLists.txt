set(PICO_CXX_ENABLE_EXCEPTIONS 1)

add_llvm_component_library(LLVMGTrackCoveragePass
  GTrackCoveragePass.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms

  DEPENDS
  intrinsics_gen

  LINK_COMPONENTS
  Core
  Support
  )

include_directories(.)
