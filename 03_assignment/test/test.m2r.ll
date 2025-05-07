; ModuleID = 'test/test.ll'
source_filename = "test/test.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z4foo2ii(i32 noundef %0, i32 noundef %1) #0 {
  br label %3

3:                                                ; preds = %15, %2
  %.01 = phi i32 [ undef, %2 ], [ %.1, %15 ]
  %4 = icmp ne i32 %0, 0
  br i1 %4, label %5, label %11

5:                                                ; preds = %3
  %6 = mul nsw i32 5, %1
  %7 = icmp ne i32 %1, 1
  br i1 %7, label %8, label %10

8:                                                ; preds = %5
  %9 = add nsw i32 %6, 2
  br label %16

10:                                               ; preds = %5
  br label %15

11:                                               ; preds = %3
  %12 = icmp ne i32 %0, 1
  br i1 %12, label %13, label %14

13:                                               ; preds = %11
  br label %16

14:                                               ; preds = %11
  br label %15

15:                                               ; preds = %14, %10
  %.1 = phi i32 [ %6, %10 ], [ %.01, %14 ]
  br label %3, !llvm.loop !6

16:                                               ; preds = %13, %8
  %.0 = phi i32 [ %9, %8 ], [ %.01, %13 ]
  ret i32 %.0
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
