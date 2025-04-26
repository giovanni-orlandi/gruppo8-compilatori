; ModuleID = 'test/test.cpp'
source_filename = "test/test.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3foov() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  store i32 2, ptr %1, align 4
  store i32 3, ptr %2, align 4
  store i32 0, ptr %6, align 4
  br label %11

11:                                               ; preds = %50, %0
  %12 = load i32, ptr %6, align 4
  %13 = load i32, ptr %1, align 4
  %14 = icmp slt i32 %12, %13
  br i1 %14, label %15, label %53

15:                                               ; preds = %11
  %16 = load i32, ptr %1, align 4
  %17 = load i32, ptr %2, align 4
  %18 = add nsw i32 %16, %17
  store i32 %18, ptr %3, align 4
  store i32 0, ptr %7, align 4
  br label %19

19:                                               ; preds = %34, %15
  %20 = load i32, ptr %7, align 4
  %21 = load i32, ptr %2, align 4
  %22 = icmp slt i32 %20, %21
  br i1 %22, label %23, label %37

23:                                               ; preds = %19
  store i32 0, ptr %8, align 4
  br label %24

24:                                               ; preds = %30, %23
  %25 = load i32, ptr %8, align 4
  %26 = icmp slt i32 %25, 100
  br i1 %26, label %27, label %33

27:                                               ; preds = %24
  %28 = load i32, ptr %1, align 4
  %29 = add nsw i32 %28, 2
  store i32 %29, ptr %5, align 4
  br label %30

30:                                               ; preds = %27
  %31 = load i32, ptr %8, align 4
  %32 = add nsw i32 %31, 1
  store i32 %32, ptr %8, align 4
  br label %24, !llvm.loop !6

33:                                               ; preds = %24
  br label %34

34:                                               ; preds = %33
  %35 = load i32, ptr %6, align 4
  %36 = add nsw i32 %35, 1
  store i32 %36, ptr %6, align 4
  br label %19, !llvm.loop !8

37:                                               ; preds = %19
  store i32 0, ptr %9, align 4
  br label %38

38:                                               ; preds = %44, %37
  %39 = load i32, ptr %9, align 4
  %40 = icmp slt i32 %39, 100
  br i1 %40, label %41, label %47

41:                                               ; preds = %38
  %42 = load i32, ptr %2, align 4
  %43 = add nsw i32 %42, 2
  store i32 %43, ptr %4, align 4
  br label %44

44:                                               ; preds = %41
  %45 = load i32, ptr %9, align 4
  %46 = add nsw i32 %45, 1
  store i32 %46, ptr %9, align 4
  br label %38, !llvm.loop !9

47:                                               ; preds = %38
  %48 = load i32, ptr %3, align 4
  %49 = add nsw i32 %48, 3
  store i32 %49, ptr %10, align 4
  br label %50

50:                                               ; preds = %47
  %51 = load i32, ptr %6, align 4
  %52 = add nsw i32 %51, 1
  store i32 %52, ptr %6, align 4
  br label %11, !llvm.loop !10

53:                                               ; preds = %11
  %54 = load i32, ptr %1, align 4
  ret i32 %54
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
!9 = distinct !{!9, !7}
!10 = distinct !{!10, !7}
