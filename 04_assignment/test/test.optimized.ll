; ModuleID = 'test/test.m2r.ll'
source_filename = "test/test.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind uwtable
define dso_local void @testarray(i32 noundef %0) #0 {
  br label %2

2:                                                ; preds = %5, %1
  %.0 = phi i32 [ 0, %1 ], [ %4, %5 ]
  %3 = mul nsw i32 3, %.0
  %4 = add nsw i32 %.0, 1
  br label %5

5:                                                ; preds = %2
  %6 = icmp slt i32 %4, %0
  br i1 %6, label %2, label %7, !llvm.loop !6

7:                                                ; preds = %5
  br label %8

8:                                                ; preds = %11, %7
  %9 = mul nsw i32 3, %.0
  %10 = add nsw i32 %.0, 1
  br label %11

11:                                               ; preds = %8
  %12 = icmp slt i32 %10, %0
  br i1 %12, label %8, label %13, !llvm.loop !8

13:                                               ; preds = %11
  ret void
}

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

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
