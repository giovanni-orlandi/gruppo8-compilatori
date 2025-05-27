; ModuleID = 'test/test.ll'
source_filename = "test/test.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [11 x i8] c"Somma: %d\0A\00", align 1
@.str.1 = private unnamed_addr constant [14 x i8] c"Prodotto: %d\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @test(i32 noundef %0) #0 {
  br label %2

2:                                                ; preds = %11, %1
  %.06 = phi i32 [ 0, %1 ], [ %3, %11 ]
  %.03 = phi i32 [ 0, %1 ], [ %.14, %11 ]
  %.02 = phi i32 [ 0, %1 ], [ %4, %11 ]
  %3 = add nsw i32 %.06, %.02
  %4 = add nsw i32 %.02, 1
  %5 = icmp sgt i32 %3, 0
  br i1 %5, label %6, label %8

6:                                                ; preds = %2
  %7 = add nsw i32 %.03, 1
  br label %10

8:                                                ; preds = %2
  %9 = add nsw i32 %.03, -1
  br label %10

10:                                               ; preds = %8, %6
  %.14 = phi i32 [ %7, %6 ], [ %9, %8 ]
  br label %11

11:                                               ; preds = %10
  %12 = icmp slt i32 %4, %0
  br i1 %12, label %2, label %13, !llvm.loop !6

13:                                               ; preds = %11
  br label %14

14:                                               ; preds = %23, %13
  %.07 = phi i32 [ 0, %13 ], [ %.18, %23 ]
  %.1 = phi i32 [ 0, %13 ], [ %15, %23 ]
  %.01 = phi i32 [ 1, %13 ], [ %16, %23 ]
  %15 = add nsw i32 %.1, 1
  %16 = mul nsw i32 %.01, %15
  %17 = icmp sgt i32 %16, 0
  br i1 %17, label %18, label %20

18:                                               ; preds = %14
  %19 = add nsw i32 %.07, 1
  br label %22

20:                                               ; preds = %14
  %21 = add nsw i32 %.07, -1
  br label %22

22:                                               ; preds = %20, %18
  %.18 = phi i32 [ %19, %18 ], [ %21, %20 ]
  br label %23

23:                                               ; preds = %22
  %24 = icmp slt i32 %15, %0
  br i1 %24, label %14, label %25, !llvm.loop !8

25:                                               ; preds = %23
  br label %26

26:                                               ; preds = %35, %25
  %.25 = phi i32 [ %.14, %25 ], [ %.3, %35 ]
  %.2 = phi i32 [ 0, %25 ], [ %28, %35 ]
  %.0 = phi i32 [ undef, %25 ], [ %27, %35 ]
  %27 = add nsw i32 %.0, %.2
  %28 = add nsw i32 %.2, 1
  %29 = icmp sgt i32 %27, 0
  br i1 %29, label %30, label %32

30:                                               ; preds = %26
  %31 = add nsw i32 %.25, 1
  br label %34

32:                                               ; preds = %26
  %33 = add nsw i32 %.25, -1
  br label %34

34:                                               ; preds = %32, %30
  %.3 = phi i32 [ %31, %30 ], [ %33, %32 ]
  br label %35

35:                                               ; preds = %34
  %36 = icmp slt i32 %28, %0
  br i1 %36, label %26, label %37, !llvm.loop !9

37:                                               ; preds = %35
  %38 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %3)
  %39 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %16)
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
!8 = distinct !{!8, !7}
!9 = distinct !{!9, !7}
