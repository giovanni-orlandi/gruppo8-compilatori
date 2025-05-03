; ModuleID = 'test/test.ll'
source_filename = "test/test.cpp"
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
  %10 = add nsw i32 %4, 2
  ret i32 0
}

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z4foo2ii(i32 noundef %0, i32 noundef %1) #0 {
  br label %3

3:                                                ; preds = %7, %2
  %.01 = phi i32 [ undef, %2 ], [ %6, %7 ]
  %.0 = phi i32 [ 0, %2 ], [ %8, %7 ]
  %4 = icmp slt i32 %.0, 10
  br i1 %4, label %5, label %9

5:                                                ; preds = %3
  %6 = add nsw i32 1, %1
  br label %7

7:                                                ; preds = %5
  %8 = add nsw i32 %.0, 1
  br label %3, !llvm.loop !8

9:                                                ; preds = %3
  %10 = add nsw i32 %.01, 2
  ret i32 0
}

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z4foo3ii(i32 noundef %0, i32 noundef %1) #0 {
  br label %3

3:                                                ; preds = %7, %2
  %.0 = phi i32 [ 0, %2 ], [ %8, %7 ]
  %4 = icmp slt i32 %.0, 10
  br i1 %4, label %5, label %9

5:                                                ; preds = %3
  %6 = add nsw i32 1, %1
  br label %7

7:                                                ; preds = %5
  %8 = add nsw i32 %.0, 1
  br label %3, !llvm.loop !9

9:                                                ; preds = %3
  ret i32 0
}

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z4foo4ii(i32 noundef %0, i32 noundef %1) #0 {
  br label %3

3:                                                ; preds = %14, %2
  %.01 = phi i32 [ %1, %2 ], [ %.1, %14 ]
  %.0 = phi i32 [ %0, %2 ], [ %15, %14 ]
  %4 = icmp eq i32 %.0, 0
  br i1 %4, label %5, label %6

5:                                                ; preds = %3
  br label %16

6:                                                ; preds = %3
  br label %7

7:                                                ; preds = %11, %6
  %.1 = phi i32 [ %.01, %6 ], [ %12, %11 ]
  %8 = add nsw i32 1, %.0
  %9 = icmp eq i32 %.1, 0
  br i1 %9, label %10, label %11

10:                                               ; preds = %7
  br label %13

11:                                               ; preds = %7
  %12 = add nsw i32 %.1, -1
  br label %7, !llvm.loop !10

13:                                               ; preds = %10
  br label %14

14:                                               ; preds = %13
  %15 = add nsw i32 %.0, -1
  br label %3, !llvm.loop !11

16:                                               ; preds = %5
  ret i32 0
}

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z4foo5iii(i32 noundef %0, i32 noundef %1, i32 noundef %2) #0 {
  br label %4

4:                                                ; preds = %15, %3
  %.01 = phi i32 [ %1, %3 ], [ %.1, %15 ]
  %.0 = phi i32 [ %0, %3 ], [ %16, %15 ]
  %5 = icmp eq i32 %.0, 0
  br i1 %5, label %6, label %7

6:                                                ; preds = %4
  br label %17

7:                                                ; preds = %4
  br label %8

8:                                                ; preds = %12, %7
  %.1 = phi i32 [ %.01, %7 ], [ %13, %12 ]
  %9 = add nsw i32 1, %2
  %10 = icmp eq i32 %.1, 0
  br i1 %10, label %11, label %12

11:                                               ; preds = %8
  br label %14

12:                                               ; preds = %8
  %13 = add nsw i32 %.1, -1
  br label %8, !llvm.loop !12

14:                                               ; preds = %11
  br label %15

15:                                               ; preds = %14
  %16 = add nsw i32 %.0, -1
  br label %4, !llvm.loop !13

17:                                               ; preds = %6
  ret i32 0
}

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z4foo6iiii(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) #0 {
  br label %5

5:                                                ; preds = %32, %4
  %.04 = phi i32 [ %3, %4 ], [ %.15, %32 ]
  %.02 = phi i32 [ %2, %4 ], [ %.13, %32 ]
  %.01 = phi i32 [ %1, %4 ], [ %.1, %32 ]
  %.0 = phi i32 [ %0, %4 ], [ %33, %32 ]
  %6 = icmp eq i32 %.0, 0
  br i1 %6, label %7, label %8

7:                                                ; preds = %5
  br label %34

8:                                                ; preds = %5
  br label %9

9:                                                ; preds = %29, %8
  %.15 = phi i32 [ %.04, %8 ], [ %.26, %29 ]
  %.13 = phi i32 [ %.02, %8 ], [ %.2, %29 ]
  %.1 = phi i32 [ %.01, %8 ], [ %30, %29 ]
  %10 = add nsw i32 %.0, 1
  %11 = icmp eq i32 %.1, 0
  br i1 %11, label %12, label %13

12:                                               ; preds = %9
  br label %31

13:                                               ; preds = %9
  br label %14

14:                                               ; preds = %26, %13
  %.26 = phi i32 [ %.15, %13 ], [ %.3, %26 ]
  %.2 = phi i32 [ %.13, %13 ], [ %27, %26 ]
  %15 = add nsw i32 %.1, 2
  %16 = icmp eq i32 %.2, 0
  br i1 %16, label %17, label %18

17:                                               ; preds = %14
  br label %28

18:                                               ; preds = %14
  br label %19

19:                                               ; preds = %23, %18
  %.3 = phi i32 [ %.26, %18 ], [ %24, %23 ]
  %20 = add nsw i32 %.2, 3
  %21 = icmp eq i32 %.3, 0
  br i1 %21, label %22, label %23

22:                                               ; preds = %19
  br label %25

23:                                               ; preds = %19
  %24 = add nsw i32 %.3, -1
  br label %19, !llvm.loop !14

25:                                               ; preds = %22
  br label %26

26:                                               ; preds = %25
  %27 = add nsw i32 %.2, -1
  br label %14, !llvm.loop !15

28:                                               ; preds = %17
  br label %29

29:                                               ; preds = %28
  %30 = add nsw i32 %.1, -1
  br label %9, !llvm.loop !16

31:                                               ; preds = %12
  br label %32

32:                                               ; preds = %31
  %33 = add nsw i32 %.0, -1
  br label %5, !llvm.loop !17

34:                                               ; preds = %7
  call void @llvm.trap()
  unreachable
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
!11 = distinct !{!11, !7}
!12 = distinct !{!12, !7}
!13 = distinct !{!13, !7}
!14 = distinct !{!14, !7}
!15 = distinct !{!15, !7}
!16 = distinct !{!16, !7}
!17 = distinct !{!17, !7}
