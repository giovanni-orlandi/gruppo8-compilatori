; ModuleID = 'test/test.m2r.ll'
source_filename = "test/test.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z4foo1ii(i32 noundef %0, i32 noundef %1) #0 {
  br label %3

3:                                                ; preds = %7, %2
  %.0 = phi i32 [ %0, %2 ], [ %8, %7 ]
  %4 = add nsw i32 1, %1
  %5 = icmp eq i32 %.0, 0
  br i1 %5, label %6, label %7

6:                                                ; preds = %3
  br label %9

7:                                                ; preds = %3
  %8 = add nsw i32 %.0, -1
  br label %3, !llvm.loop !6

9:                                                ; preds = %6
  br label %10

10:                                               ; preds = %14, %9
  %.1 = phi i32 [ %.0, %9 ], [ %15, %14 ]
  %11 = add nsw i32 1, %1
  %12 = icmp eq i32 %.1, 0
  br i1 %12, label %13, label %14

13:                                               ; preds = %10
  br label %16

14:                                               ; preds = %10
  %15 = add nsw i32 %.1, -1
  br label %10, !llvm.loop !8

16:                                               ; preds = %13
  %17 = add nsw i32 %11, 2
  ret i32 0
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
