; ModuleID = 'b1.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32"
target triple = "i386-pc-linux-gnu"

@str = internal constant [12 x i8] c"hello world\00"
@str2 = internal constant [13 x i8] c"second hello\00"

define i32 @main() nounwind {
bb.nph5:
  br label %0

; <label>:0                                       ; preds = %0, %bb.nph5
  %i.04 = phi i32 [ 0, %bb.nph5 ], [ %1, %0 ]
  %puts = tail call i32 @puts(i8* getelementptr inbounds ([12 x i8]* @str, i32 0, i32 0))
  %1 = add nsw i32 %i.04, 1
  %exitcond6 = icmp eq i32 %1, 6
  br i1 %exitcond6, label %bb.nph, label %0

bb.nph:                                           ; preds = %bb.nph, %0
  %i1.03 = phi i32 [ %2, %bb.nph ], [ 0, %0 ]
  %puts2 = tail call i32 @puts(i8* getelementptr inbounds ([13 x i8]* @str2, i32 0, i32 0))
  %2 = add nsw i32 %i1.03, 1
  %exitcond = icmp eq i32 %2, 6
  br i1 %exitcond, label %._crit_edge, label %bb.nph

._crit_edge:                                      ; preds = %bb.nph
  ret i32 0
}

declare i32 @puts(i8* nocapture) nounwind

declare void @klee_make_symbolic(i32*, i32)
