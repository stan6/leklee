//===-- LoopExtended.cpp - Loop unroller pass -------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This pass implements a simple loop unroller.  It works best when loops have
// been canonicalized by the -indvars pass, allowing it to determine the trip
// counts of loops easily.
//===----------------------------------------------------------------------===//

//#define DEBUG_TYPE "le"
#include "llvm/Support/IRBuilder.h"
#include "llvm/IntrinsicInst.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Function.h"
#include "llvm/Pass.h"
#include "llvm/Module.h"
#include "llvm/PassSupport.h"
#include "llvm/Analysis/CodeMetrics.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"
//#include "llvm/Transforms/Utils/UnrollLoop.h"
#include <climits>

using namespace llvm;

namespace {
  class LoopExtended : public ModulePass {
  public:
    static char ID; // Pass ID, replacement for typeid
    LoopExtended() : ModulePass(ID) {
     	//initializeLoopExtendedPass(*PassRegistry::getPassRegistry());
    }
   static const unsigned NoThreshold = UINT_MAX;
    
    // Threshold to use when optsize is specified (and there is no
    // explicit -unroll-threshold).
    static const unsigned OptSizeUnrollThreshold = 50;
    
    unsigned CurrentThreshold;
    Function* hook;
    
   
   //bool runOnModule(Module &M);
   bool runOnLoop(Loop *L);
   //bool runOnBasicBlock(Function::iterator &BB);

virtual bool runOnModule(Module &M)
 {
            Constant *hookFunc;
            hookFunc = M.getOrInsertFunction("klee_make_symbolic", Type::getVoidTy(M.getContext()), Type::getInt32PtrTy(M.getContext()),Type::getInt32Ty(M.getContext()),NULL);
              
            hook= cast<Function>(hookFunc);


            for(Module::iterator F = M.begin(), E = M.end(); F!= E; ++F)
            {

                for(Function::iterator BB = F->begin(), E = F->end(); BB != E; ++BB)
                {
                    LoopExtended::runOnBasicBlock(BB);
                }
            }

            return false;
 }


 virtual bool runOnBasicBlock(Function::iterator &BB)
  {
            for(BasicBlock::iterator BI = BB->begin(), BE = BB->end(); BI != BE; ++BI)          
            {
                    if(isa<LoadInst>(&(*BI)) )
                    {
                            LoadInst *CI = dyn_cast<LoadInst>(BI);
                            Instruction *newInst = CallInst::Create(hook, "");
                            BB->getInstList().insert((Instruction*)CI, newInst);                        
                    }
                  
            }
            return true;
 }

    /// This transformation requires natural loop information & requires that
    /// loop preheaders be inserted into the CFG...
    ///
    virtual void getAnalysisUsage(AnalysisUsage &AU) const {
      AU.setPreservesCFG();
      AU.addRequired<LoopInfo>();
      AU.addPreserved<LoopInfo>();
      AU.addRequiredID(LoopSimplifyID);
      AU.addPreservedID(LoopSimplifyID);
      AU.addRequiredID(LCSSAID);
      AU.addPreservedID(LCSSAID);
      AU.addPreserved<ScalarEvolution>();
      // FIXME: Loop unroll requires LCSSA. And LCSSA requires dom info.
      // If loop unroll does not preserve dom info then LCSSA pass on next
      // loop will receive invalid dom info.
      // For now, recreate dom info, if loop is unrolled.
      AU.addPreserved<DominatorTree>();
    }//end of getAnalysisUsage
};
}  
char LoopExtended::ID = 0;
static RegisterPass<LoopExtended> X("loop-extend", "Loop Extended Pass", false, false);
INITIALIZE_PASS_BEGIN(LoopExtended, "loop-extend", "Extended loops", false, false)
INITIALIZE_PASS_DEPENDENCY(LoopInfo)
INITIALIZE_PASS_DEPENDENCY(LoopSimplify)
INITIALIZE_PASS_DEPENDENCY(LCSSA)
INITIALIZE_PASS_END(LoopExtended, "loop-extend", "Extended loops", false, false)

//Pass *llvm::createLoopExtendedPass() { return new LoopExtended(); }

  
bool LoopExtended::runOnLoop(Loop *L/*, LPPassManager &LPM*/) {
  //LoopInfo *LI = &getAnalysis<LoopInfo>();
 
  BasicBlock *Header = L->getHeader();
  //BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", L->getHeader()->getParent());
  //Builder.SetInsertPoint(bb);
  //std::vector<BlockT*> bb=L->getBlocksVector();
int i=0;
int loop=0;
  for (Loop::block_iterator bbit = L->block_begin(), bbie = L->block_end(); bbit != bbie;
   ++bbit) { // Make loop work given updates	
	errs()<<"Loop executed"<<loop<<'\n';
     for (BasicBlock::const_iterator II = (*bbit)->begin(), E = (*bbit)->end(); II != E; ++II) {
	errs()<<"BB executed"<<i<<'\n';
	i++;
	if(isa<StoreInst>(II)){
		//const StoreInst *SI = dyn_cast<StoreInst>(II);
		//const Value* val=SI->getValueOperand();
		errs()<<"Store ins"<<'\n';
	}
	else if(isa<PHINode>(II)){
		const PHINode *PI = dyn_cast<PHINode>(II);
		const Value* val=PI->getIncomingValueForBlock(*bbit);
		errs()<<"PHINode"<<val->getName()<<'\n';
	}

    }
  // int trip_count;
   //CallInst * beforeCall = CallInst::Create(klee_make_symbolic(&trip_count,sizeof trip_count))// INSERT THIS
   //beforeCall->insertBefore(i);
/*
   if (!i->isTerminator()) {
      CallInst * afterCall = // INSERT THIS
      afterCall->insertAfter(i);
   }
*/
	loop++;
  }
  //return retval;
  errs() << "Loop Extended: F[" << Header->getParent()->getName()
        << "] Loop %" << Header->getName() << "\n";
  //(void)Header;
  
  // Determine the current unrolling threshold.  While this is normally set
  // from ExtendedThreshold, it is overridden to a smaller value if the current
  // function is marked as optimize-for-size, and the unroll threshold was
  // not user specified.
  //CurrentThreshold = ExtendedThreshold;
  //if (Header->getParent()->hasFnAttr(Attribute::OptimizeForSize) )
    //CurrentThreshold = OptSizeExtendedThreshold;

  // Find trip count
  unsigned TripCount = L->getSmallConstantTripCount();
  //unsigned Count = ExtendedCount;
  errs() << "Hello: ";
  errs().write_escaped("TripCount:") << TripCount <<'\n';
  

  // Extended the loop.
  Function *F = L->getHeader()->getParent();
 // if (!ExtendedLoop(L, Count, LI, &LPM))
   // return false;

  // FIXME: Reconstruct dom info, because it is not preserved properly.
  if (DominatorTree *DT = getAnalysisIfAvailable<DominatorTree>())
    DT->runOnFunction(*F);
  return true;
}

