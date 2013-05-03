; ModuleID = 'instrumented.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32"
target triple = "i386-pc-linux-gnu"

@str = internal constant [12 x i8] c"hello world\00"

define i32 @main() nounwind {
bb.nph:
  br label %0

; <label>:0                                       ; preds = %0, %bb.nph
  %i.01 = phi i32 [ 0, %bb.nph ], [ %1, %0 ]
  %puts = tail call i32 @puts(i8* getelementptr inbounds ([12 x i8]* @str, i32 0, i32 0))
  %1 = add nsw i32 %i.01, 1
  %exitcond = icmp eq i32 %1, 6
  br i1 %exitcond, label %._crit_edge, label %0

._crit_edge:                                      ; preds = %0
  ret i32 0
}

declare i32 @puts(i8* nocapture) nounwind

declare void @klee_make_symbolic(i32*, i32)
