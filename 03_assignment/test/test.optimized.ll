; ModuleID = 'test/test.m2r.ll'
source_filename = "test/test.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3foov() #0 {
  br label %1

1:                                                ; preds = %26, %0
  %.02 = phi i32 [ 0, %0 ], [ %27, %26 ]
  %2 = icmp slt i32 %.02, 2
  br i1 %2, label %3, label %28

3:                                                ; preds = %1
  %4 = add nsw i32 2, 3
  br label %5

5:                                                ; preds = %15, %3
  %.1 = phi i32 [ %.02, %3 ], [ %16, %15 ]
  %6 = icmp slt i32 0, 3
  br i1 %6, label %7, label %17

7:                                                ; preds = %5
  br label %8

8:                                                ; preds = %12, %7
  %.01 = phi i32 [ 0, %7 ], [ %13, %12 ]
  %9 = icmp slt i32 %.01, 100
  br i1 %9, label %10, label %14

10:                                               ; preds = %8
  %11 = add nsw i32 2, 2
  br label %12

12:                                               ; preds = %10
  %13 = add nsw i32 %.01, 1
  br label %8, !llvm.loop !6

14:                                               ; preds = %8
  br label %15

15:                                               ; preds = %14
  %16 = add nsw i32 %.1, 1
  br label %5, !llvm.loop !8

17:                                               ; preds = %5
  br label %18

18:                                               ; preds = %22, %17
  %.0 = phi i32 [ 0, %17 ], [ %23, %22 ]
  %19 = icmp slt i32 %.0, 100
  br i1 %19, label %20, label %24

20:                                               ; preds = %18
  %21 = add nsw i32 3, 2
  br label %22

22:                                               ; preds = %20
  %23 = add nsw i32 %.0, 1
  br label %18, !llvm.loop !9

24:                                               ; preds = %18
  %25 = add nsw i32 %4, 3
  br label %26

26:                                               ; preds = %24
  %27 = add nsw i32 %.1, 1
  br label %1, !llvm.loop !10

28:                                               ; preds = %1
  ret i32 2
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
!9 = distinct !{!9, !7}
!10 = distinct !{!10, !7}
