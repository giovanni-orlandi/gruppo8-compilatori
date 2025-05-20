; ModuleID = 'test/test.ll'
source_filename = "test/test.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local void @_Z5test2i(i32 noundef %0) #0 {
  br label %2

2:                                                ; preds = %4, %1
  %.02 = phi i32 [ 0, %1 ], [ %6, %4 ]
  %.01 = phi i32 [ 2, %1 ], [ %5, %4 ]
  %3 = icmp slt i32 %.02, 50
  br i1 %3, label %4, label %7

4:                                                ; preds = %2
  %5 = add nsw i32 %.01, 1
  %6 = add nsw i32 %.02, 1
  br label %2, !llvm.loop !6

7:                                                ; preds = %2
  br label %8

8:                                                ; preds = %10, %7
  %.1 = phi i32 [ %.01, %7 ], [ %11, %10 ]
  %.0 = phi i32 [ 0, %7 ], [ %12, %10 ]
  %9 = icmp slt i32 %.0, 50
  br i1 %9, label %10, label %13

10:                                               ; preds = %8
  %11 = add nsw i32 %.1, 1
  %12 = add nsw i32 %.0, 1
  br label %8, !llvm.loop !8

13:                                               ; preds = %8
  ret void
}

attributes #0 = { mustprogress noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 19.1.1 (1ubuntu1~24.04.2)"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
