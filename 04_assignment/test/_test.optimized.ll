; ModuleID = 'test/test.m2r.ll'
source_filename = "test/test.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local void @_Z4testii(i32 noundef %0, i32 noundef %1) #0 {
  %3 = icmp slt i32 %0, 0
  br i1 %3, label %4, label %10

4:                                                ; preds = %2
  br label %5

5:                                                ; preds = %7, %4
  %.0 = phi i32 [ 0, %4 ], [ %6, %7 ]
  %6 = add nsw i32 %.0, 1
  br label %7

7:                                                ; preds = %5
  %8 = icmp slt i32 %6, %0
  br i1 %8, label %5, label %9, !llvm.loop !6

9:                                                ; preds = %7
  br label %10

10:                                               ; preds = %9, %2
  %.1 = phi i32 [ %6, %9 ], [ 0, %2 ]
  %11 = icmp slt i32 %0, 0
  br i1 %11, label %12, label %18

12:                                               ; preds = %10
  br label %13

13:                                               ; preds = %15, %12
  %.2 = phi i32 [ %.1, %12 ], [ %14, %15 ]
  %14 = add nsw i32 %.2, 1
  br label %15

15:                                               ; preds = %13
  %16 = icmp slt i32 %14, %0
  br i1 %16, label %13, label %17, !llvm.loop !8

17:                                               ; preds = %15
  br label %18

18:                                               ; preds = %17, %10
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
