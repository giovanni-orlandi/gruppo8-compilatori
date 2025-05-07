; ModuleID = 'test/test.cpp'
source_filename = "test/test.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z4foo2ii(i32 noundef %0, i32 noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i32 %0, ptr %4, align 4
  store i32 %1, ptr %5, align 4
  br label %8

8:                                                ; preds = %2, %27
  %9 = load i32, ptr %4, align 4
  %10 = icmp ne i32 %9, 0
  br i1 %10, label %11, label %21

11:                                               ; preds = %8
  %12 = load i32, ptr %5, align 4
  %13 = mul nsw i32 5, %12
  store i32 %13, ptr %7, align 4
  %14 = load i32, ptr %5, align 4
  %15 = icmp ne i32 %14, 1
  br i1 %15, label %16, label %20

16:                                               ; preds = %11
  %17 = load i32, ptr %7, align 4
  %18 = add nsw i32 %17, 2
  store i32 %18, ptr %6, align 4
  %19 = load i32, ptr %6, align 4
  store i32 %19, ptr %3, align 4
  br label %28

20:                                               ; preds = %11
  br label %27

21:                                               ; preds = %8
  %22 = load i32, ptr %4, align 4
  %23 = icmp ne i32 %22, 1
  br i1 %23, label %24, label %26

24:                                               ; preds = %21
  %25 = load i32, ptr %7, align 4
  store i32 %25, ptr %3, align 4
  br label %28

26:                                               ; preds = %21
  br label %27

27:                                               ; preds = %26, %20
  br label %8, !llvm.loop !6

28:                                               ; preds = %24, %16
  %29 = load i32, ptr %3, align 4
  ret i32 %29
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
