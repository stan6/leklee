//===- Hello.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements two versions of the LLVM "Hello World" pass described
// in docs/WritingAnLLVMPass.html
//
//===----------------------------------------------------------------------===//

#include "llvm/Pass.h"
#include "llvm/Function.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
  // Hello - The first implementation, without getAnalysisUsage.
  struct Seryozha : public FunctionPass {
    static char ID; // Pass identification, replacement for typeid
    Seryozha() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
      errs() << "Seryozha: " << F.getName() << "\n";
      return false;
    }
  };
}

char Seryozha::ID = 0;
static RegisterPass<Seryozha> X("seryozha", "Hello World Pass", false, false);


