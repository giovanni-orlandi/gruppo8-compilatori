; ModuleID = 'test/test.m2r.ll'
source_filename = "test/test.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [11 x i8] c"Somma: %d\0A\00", align 1
@.str.1 = private unnamed_addr constant [14 x i8] c"Prodotto: %d\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local void @test(i32 noundef %0) #0 {
  br label %2

2:                                                ; preds = %9, %1
  %.02 = phi i32 [ 0, %1 ], [ %4, %9 ]
  %.01 = phi i32 [ 0, %1 ], [ %3, %9 ]
  %.0 = phi i32 [ 1, %1 ], [ %7, %9 ]
  %3 = add nsw i32 %.01, 2
  %4 = add nsw i32 %.02, %3
  br label %5

5:                                                ; preds = %2
  %6 = add nsw i32 %.01, 3
  %7 = mul nsw i32 %.0, %6
  %8 = add nsw i32 %.01, 2
  br label %9

9:                                                ; preds = %5
  %10 = icmp slt i32 %8, %0
  br i1 %10, label %2, label %11, !llvm.loop !6

11:                                               ; preds = %9
  %12 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %4)
  %13 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %7)
  ret void
}

declare i32 @printf(ptr noundef, ...) #1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 {
  call void @test(i32 noundef 5)
  ret i32 0
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
