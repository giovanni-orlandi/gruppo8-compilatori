; ModuleID = 'test/test.c'
source_filename = "test/test.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local void @_Z4testii(i32 noundef %0, i32 noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store i32 %0, ptr %3, align 4
  store i32 %1, ptr %4, align 4
  store i32 0, ptr %5, align 4
  store i32 0, ptr %6, align 4
  %7 = load i32, ptr %3, align 4
  %8 = icmp slt i32 5, %7
  br i1 %8, label %9, label %18

9:                                                ; preds = %2
  br label %10

10:                                               ; preds = %13, %9
  %11 = load i32, ptr %6, align 4
  %12 = add nsw i32 %11, 1
  store i32 %12, ptr %6, align 4
  br label %13

13:                                               ; preds = %10
  %14 = load i32, ptr %5, align 4
  %15 = load i32, ptr %3, align 4
  %16 = icmp slt i32 %14, %15
  br i1 %16, label %10, label %17, !llvm.loop !6

17:                                               ; preds = %13
  br label %18

18:                                               ; preds = %17, %2
  %19 = load i32, ptr %4, align 4
  %20 = add nsw i32 %19, 1
  store i32 %20, ptr %4, align 4
  %21 = load i32, ptr %3, align 4
  %22 = icmp sgt i32 %21, 5
  br i1 %22, label %23, label %32

23:                                               ; preds = %18
  br label %24

24:                                               ; preds = %27, %23
  %25 = load i32, ptr %4, align 4
  %26 = add nsw i32 %25, 1
  store i32 %26, ptr %4, align 4
  br label %27

27:                                               ; preds = %24
  %28 = load i32, ptr %5, align 4
  %29 = load i32, ptr %3, align 4
  %30 = icmp slt i32 %28, %29
  br i1 %30, label %24, label %31, !llvm.loop !8

31:                                               ; preds = %27
  br label %32

32:                                               ; preds = %31, %18
  ret void
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
!8 = distinct !{!8, !7}
