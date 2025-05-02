; ModuleID = 'test/test.cpp'
source_filename = "test/test.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooiiii(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) #0 {
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  store i32 %0, ptr %5, align 4
  store i32 %1, ptr %6, align 4
  store i32 %2, ptr %7, align 4
  store i32 %3, ptr %8, align 4
  store i32 0, ptr %12, align 4
  store i32 0, ptr %13, align 4
  br label %14

14:                                               ; preds = %4, %34
  %15 = load i32, ptr %13, align 4
  %16 = add nsw i32 %15, 1
  store i32 %16, ptr %13, align 4
  %17 = load i32, ptr %8, align 4
  %18 = icmp slt i32 %17, 10
  br i1 %18, label %19, label %24

19:                                               ; preds = %14
  %20 = load i32, ptr %10, align 4
  %21 = icmp slt i32 %20, 5
  br i1 %21, label %22, label %23

22:                                               ; preds = %19
  br label %35

23:                                               ; preds = %19
  br label %34

24:                                               ; preds = %14
  %25 = load i32, ptr %5, align 4
  %26 = load i32, ptr %6, align 4
  %27 = add nsw i32 %25, %26
  store i32 %27, ptr %9, align 4
  %28 = load i32, ptr %9, align 4
  %29 = sdiv i32 %28, 2
  store i32 %29, ptr %10, align 4
  %30 = load i32, ptr %9, align 4
  %31 = add nsw i32 %30, 310
  store i32 %31, ptr %7, align 4
  %32 = load i32, ptr %11, align 4
  %33 = add nsw i32 %32, 3
  store i32 %33, ptr %12, align 4
  br label %34

34:                                               ; preds = %24, %23
  br label %14, !llvm.loop !6

35:                                               ; preds = %22
  %36 = load i32, ptr %12, align 4
  ret i32 %36
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
