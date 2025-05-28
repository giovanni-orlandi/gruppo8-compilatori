; ModuleID = 'test/rotated/hard.ll'
source_filename = "test/rotated/hard.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [11 x i8] c"Somma: %d\0A\00", align 1
@.str.1 = private unnamed_addr constant [14 x i8] c"Prodotto: %d\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @test(i32 noundef %0) #0 {
  %2 = icmp sgt i32 %0, 0
  br i1 %2, label %3, label %16

3:                                                ; preds = %1
  br label %4

4:                                                ; preds = %13, %3
  %.07 = phi i32 [ 0, %3 ], [ %5, %13 ]
  %.05 = phi i32 [ 0, %3 ], [ %.16, %13 ]
  %.03 = phi i32 [ 0, %3 ], [ %6, %13 ]
  %5 = add nsw i32 %.07, %.03
  %6 = add nsw i32 %.03, 1
  %7 = icmp sgt i32 %5, 0
  br i1 %7, label %8, label %10

8:                                                ; preds = %4
  %9 = add nsw i32 %.05, 1
  br label %12

10:                                               ; preds = %4
  %11 = add nsw i32 %.05, -1
  br label %12

12:                                               ; preds = %10, %8
  %.16 = phi i32 [ %9, %8 ], [ %11, %10 ]
  br label %13

13:                                               ; preds = %12
  %14 = icmp slt i32 %6, %0
  br i1 %14, label %4, label %15, !llvm.loop !6

15:                                               ; preds = %13
  br label %16

16:                                               ; preds = %15, %1
  %.18 = phi i32 [ %5, %15 ], [ 0, %1 ]
  %17 = icmp sgt i32 %0, 0
  br i1 %17, label %18, label %31

18:                                               ; preds = %16
  br label %19

19:                                               ; preds = %28, %18
  %.14 = phi i32 [ 0, %18 ], [ %20, %28 ]
  %.01 = phi i32 [ 0, %18 ], [ %.12, %28 ]
  %.0 = phi i32 [ 1, %18 ], [ %21, %28 ]
  %20 = add nsw i32 %.14, 1
  %21 = mul nsw i32 %.0, %20
  %22 = icmp sgt i32 %21, 0
  br i1 %22, label %23, label %25

23:                                               ; preds = %19
  %24 = add nsw i32 %.01, 1
  br label %27

25:                                               ; preds = %19
  %26 = add nsw i32 %.01, -1
  br label %27

27:                                               ; preds = %25, %23
  %.12 = phi i32 [ %24, %23 ], [ %26, %25 ]
  br label %28

28:                                               ; preds = %27
  %29 = icmp slt i32 %20, %0
  br i1 %29, label %19, label %30, !llvm.loop !8

30:                                               ; preds = %28
  br label %31

31:                                               ; preds = %30, %16
  %.1 = phi i32 [ %21, %30 ], [ 1, %16 ]
  %32 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %.18)
  %33 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %.1)
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
