; ModuleID = 'test/rotated/1_rotated_guarded.ll'
source_filename = "test/rotated/1_rotated_guarded.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [11 x i8] c"Somma: %d\0A\00", align 1
@.str.1 = private unnamed_addr constant [14 x i8] c"Prodotto: %d\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @test(i32 noundef %0) #0 {
  %2 = icmp sgt i32 %0, 0
  br i1 %2, label %3, label %10

3:                                                ; preds = %1
  br label %4

4:                                                ; preds = %7, %3
  %.03 = phi i32 [ 0, %3 ], [ %6, %7 ]
  %.01 = phi i32 [ 0, %3 ], [ %5, %7 ]
  %5 = add nsw i32 %.01, %.03
  %6 = add nsw i32 %.03, 1
  br label %7

7:                                                ; preds = %4
  %8 = icmp slt i32 %6, %0
  br i1 %8, label %4, label %9, !llvm.loop !6

9:                                                ; preds = %7
  br label %10

10:                                               ; preds = %9, %1
  %.12 = phi i32 [ %5, %9 ], [ 0, %1 ]
  %11 = icmp sgt i32 %0, 0
  br i1 %11, label %12, label %19

12:                                               ; preds = %10
  br label %13

13:                                               ; preds = %16, %12
  %.14 = phi i32 [ 0, %12 ], [ %14, %16 ]
  %.0 = phi i32 [ 1, %12 ], [ %15, %16 ]
  %14 = add nsw i32 %.14, 1
  %15 = mul nsw i32 %.0, %14
  br label %16

16:                                               ; preds = %13
  %17 = icmp slt i32 %14, %0
  br i1 %17, label %13, label %18, !llvm.loop !8

18:                                               ; preds = %16
  br label %19

19:                                               ; preds = %18, %10
  %.1 = phi i32 [ %15, %18 ], [ 1, %10 ]
  %20 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %.12)
  %21 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %.1)
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
