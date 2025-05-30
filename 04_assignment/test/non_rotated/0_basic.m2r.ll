; ModuleID = 'test/non_rotated/0_basic.ll'
source_filename = "test/non_rotated/0_basic.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [11 x i8] c"Somma: %d\0A\00", align 1
@.str.1 = private unnamed_addr constant [14 x i8] c"Prodotto: %d\0A\00", align 1
@.str.2 = private unnamed_addr constant [10 x i8] c"Gugu: %d\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local void @test(i32 noundef %0) #0 {
  br label %2

2:                                                ; preds = %4, %1
  %.04 = phi i32 [ 0, %1 ], [ %6, %4 ]
  %.01 = phi i32 [ 0, %1 ], [ %5, %4 ]
  %3 = icmp slt i32 %.01, %0
  br i1 %3, label %4, label %7

4:                                                ; preds = %2
  %5 = add nsw i32 %.01, 1
  %6 = add nsw i32 %.04, %5
  br label %2, !llvm.loop !6

7:                                                ; preds = %2
  br label %8

8:                                                ; preds = %10, %7
  %.05 = phi i32 [ 1, %7 ], [ %12, %10 ]
  %.02 = phi i32 [ 0, %7 ], [ %11, %10 ]
  %9 = icmp slt i32 %.02, %0
  br i1 %9, label %10, label %13

10:                                               ; preds = %8
  %11 = add nsw i32 %.02, 1
  %12 = mul nsw i32 %.05, %11
  br label %8, !llvm.loop !8

13:                                               ; preds = %8
  br label %14

14:                                               ; preds = %16, %13
  %.03 = phi i32 [ 0, %13 ], [ %17, %16 ]
  %.0 = phi i32 [ 0, %13 ], [ %18, %16 ]
  %15 = icmp slt i32 %.03, %0
  br i1 %15, label %16, label %19

16:                                               ; preds = %14
  %17 = add nsw i32 %.03, 1
  %18 = sub nsw i32 %.0, %17
  br label %14, !llvm.loop !9

19:                                               ; preds = %14
  %20 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %.04)
  %21 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %.05)
  %22 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, i32 noundef %.0)
  ret void
}

declare i32 @printf(ptr noundef, ...) #1

; Function Attrs: noinline nounwind uwtable
define dso_local void @main() #0 {
  call void @test(i32 noundef 4)
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
