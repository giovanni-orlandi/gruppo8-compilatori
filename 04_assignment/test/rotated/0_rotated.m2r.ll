; ModuleID = 'test/rotated/0_rotated.ll'
source_filename = "test/rotated/0_rotated.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [11 x i8] c"Somma: %d\0A\00", align 1
@.str.1 = private unnamed_addr constant [14 x i8] c"Prodotto: %d\0A\00", align 1
@.str.2 = private unnamed_addr constant [7 x i8] c"a: %d\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @test(i32 noundef %0) #0 {
  br label %2

2:                                                ; preds = %5, %1
  %.03 = phi i32 [ 0, %1 ], [ %3, %5 ]
  %.02 = phi i32 [ 0, %1 ], [ %4, %5 ]
  %3 = add nsw i32 %.03, %.02
  %4 = add nsw i32 %.02, 1
  br label %5

5:                                                ; preds = %2
  %6 = icmp slt i32 %4, %0
  br i1 %6, label %2, label %7, !llvm.loop !6

7:                                                ; preds = %5
  br label %8

8:                                                ; preds = %11, %7
  %.1 = phi i32 [ 0, %7 ], [ %9, %11 ]
  %.01 = phi i32 [ 1, %7 ], [ %10, %11 ]
  %9 = add nsw i32 %.1, 1
  %10 = mul nsw i32 %.01, %9
  br label %11

11:                                               ; preds = %8
  %12 = icmp slt i32 %9, %0
  br i1 %12, label %8, label %13, !llvm.loop !8

13:                                               ; preds = %11
  br label %14

14:                                               ; preds = %17, %13
  %.2 = phi i32 [ 0, %13 ], [ %15, %17 ]
  %.0 = phi i32 [ 0, %13 ], [ %16, %17 ]
  %15 = add nsw i32 %.2, 1
  %16 = sub nsw i32 %.0, %15
  br label %17

17:                                               ; preds = %14
  %18 = icmp slt i32 %15, %0
  br i1 %18, label %14, label %19, !llvm.loop !9

19:                                               ; preds = %17
  %20 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %3)
  %21 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %10)
  %22 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, i32 noundef %16)
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
