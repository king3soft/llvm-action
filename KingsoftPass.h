//===-- CFGuard.h - CFGuard Transformations ---------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===---------------------------------------------------------------------===//
// Windows Control Flow Guard passes (/guard:cf).
//===---------------------------------------------------------------------===//

#ifndef LLVM_TRANSFORMS_KINGSOFTPASS_H
#define LLVM_TRANSFORMS_KINGSOFTPASS_H

namespace llvm {

class FunctionPass;

// FunctionPass *createFunctionCountPass();

FunctionPass *createGTrackCoveragePass();

} // namespace llvm

#endif
