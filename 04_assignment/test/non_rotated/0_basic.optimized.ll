; ModuleID = 'test/non_rotated/0_basic.m2r.ll'
source_filename = "test/non_rotated/0_basic.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [11 x i8] c"Somma: %d\0A\00", align 1
@.str.1 = private unnamed_addr constant [14 x i8] c"Prodotto: %d\0A\00", align 1
@.str.2 = private unnamed_addr constant [10 x i8] c"Gugu: %d\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local void @test(i32 noundef %0) #0 {
  br label %2

2:                                                ; preds = %7, %1
  %.03 = phi i32 [ 0, %1 ], [ %6, %7 ]
  %.01 = phi i32 [ 0, %1 ], [ %5, %7 ]
  %.02 = phi i32 [ 0, %1 ], [ %8, %7 ]
  %.0 = phi i32 [ 1, %1 ], [ %9, %7 ]
  %3 = icmp slt i32 %.01, %0
  br i1 %3, label %4, label %10

4:                                                ; preds = %2
  %5 = add nsw i32 %.01, 1
  %6 = add nsw i32 %.03, %5
  br label %7, !llvm.loop !6

7:                                                ; preds = %4
  %8 = add nsw i32 %.02, 1
  %9 = mul nsw i32 %.0, %8
  br label %2, !llvm.loop !8

10:                                               ; preds = %2
  %11 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %.03)
  %12 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %.0)
  %13 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, i32 noundef 0)
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
