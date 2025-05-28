; ModuleID = 'test/test.m2r.ll'
source_filename = "test/test.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [11 x i8] c"Somma: %d\0A\00", align 1
@.str.1 = private unnamed_addr constant [14 x i8] c"Prodotto: %d\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @test(i32 noundef %0) #0 {
  br label %2

2:                                                ; preds = %20, %1
  %.06 = phi i32 [ 0, %1 ], [ %3, %20 ]
  %.04 = phi i32 [ 0, %1 ], [ %.15, %20 ]
  %.02 = phi i32 [ 0, %1 ], [ %4, %20 ]
  %.01 = phi i32 [ 0, %1 ], [ %.1, %20 ]
  %.0 = phi i32 [ 1, %1 ], [ %13, %20 ]
  %3 = add nsw i32 %.06, %.02
  %4 = add nsw i32 %.02, 1
  %5 = icmp sgt i32 %3, 0
  br i1 %5, label %6, label %8

6:                                                ; preds = %2
  %7 = add nsw i32 %.04, 1
  br label %10

8:                                                ; preds = %2
  %9 = add nsw i32 %.04, -1
  br label %10

10:                                               ; preds = %8, %6
  %.15 = phi i32 [ %7, %6 ], [ %9, %8 ]
  br label %11

11:                                               ; preds = %10
  %12 = add nsw i32 %.02, 1
  %13 = mul nsw i32 %.0, %12
  %14 = icmp sgt i32 %13, 0
  br i1 %14, label %15, label %17

15:                                               ; preds = %11
  %16 = add nsw i32 %.01, 1
  br label %19

17:                                               ; preds = %11
  %18 = add nsw i32 %.01, -1
  br label %19

19:                                               ; preds = %17, %15
  %.1 = phi i32 [ %16, %15 ], [ %18, %17 ]
  br label %20

20:                                               ; preds = %19
  %21 = icmp slt i32 %12, %0
  br i1 %21, label %2, label %22, !llvm.loop !6

22:                                               ; preds = %20
  %23 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %3)
  %24 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %13)
  ret i32 undef
}

declare i32 @printf(ptr noundef, ...) #1

; Function Attrs: noinline nounwind uwtable
define dso_local void @main() #0 {
  %1 = call i32 @test(i32 noundef 4)
  ret void
}

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

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
