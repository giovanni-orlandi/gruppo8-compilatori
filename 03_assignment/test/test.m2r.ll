; ModuleID = 'test/test.ll'
source_filename = "test/test.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooiiii(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) #0 {
  br label %5

5:                                                ; preds = %17, %4
  %.02 = phi i32 [ undef, %4 ], [ %.13, %17 ]
  %.01 = phi i32 [ 0, %4 ], [ %.1, %17 ]
  %.0 = phi i32 [ 0, %4 ], [ %6, %17 ]
  %6 = add nsw i32 %.0, 1
  %7 = icmp slt i32 %3, 10
  br i1 %7, label %8, label %12

8:                                                ; preds = %5
  %9 = icmp slt i32 %.02, 5
  br i1 %9, label %10, label %11

10:                                               ; preds = %8
  br label %18

11:                                               ; preds = %8
  br label %17

12:                                               ; preds = %5
  %13 = add nsw i32 %0, %1
  %14 = sdiv i32 %13, 2
  %15 = add nsw i32 %13, 310
  %16 = add nsw i32 undef, 3
  br label %17

17:                                               ; preds = %12, %11
  %.13 = phi i32 [ %.02, %11 ], [ %14, %12 ]
  %.1 = phi i32 [ %.01, %11 ], [ %16, %12 ]
  br label %5, !llvm.loop !6

18:                                               ; preds = %10
  ret i32 %.01
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
