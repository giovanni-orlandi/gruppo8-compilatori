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
  store i32 2, ptr %1, align 4
  store i32 3, ptr %2, align 4
  store i32 0, ptr %3, align 4
  br label %10

10:                                               ; preds = %45, %0
  %11 = load i32, ptr %3, align 4
  %12 = load i32, ptr %1, align 4
  %13 = icmp slt i32 %11, %12
  br i1 %13, label %14, label %48

14:                                               ; preds = %10
  %15 = load i32, ptr %1, align 4
  %16 = load i32, ptr %2, align 4
  %17 = add nsw i32 %15, %16
  store i32 %17, ptr %4, align 4
  store i32 0, ptr %5, align 4
  br label %18

18:                                               ; preds = %31, %14
  %19 = load i32, ptr %5, align 4
  %20 = load i32, ptr %2, align 4
  %21 = icmp slt i32 %19, %20
  br i1 %21, label %22, label %34

22:                                               ; preds = %18
  store i32 0, ptr %6, align 4
  br label %23

23:                                               ; preds = %27, %22
  %24 = load i32, ptr %6, align 4
  %25 = icmp slt i32 %24, 100
  br i1 %25, label %26, label %30

26:                                               ; preds = %23
  store i32 2, ptr %7, align 4
  br label %27

27:                                               ; preds = %26
  %28 = load i32, ptr %6, align 4
  %29 = add nsw i32 %28, 1
  store i32 %29, ptr %6, align 4
  br label %23, !llvm.loop !6

30:                                               ; preds = %23
  br label %31

31:                                               ; preds = %30
  %32 = load i32, ptr %3, align 4
  %33 = add nsw i32 %32, 1
  store i32 %33, ptr %3, align 4
  br label %18, !llvm.loop !8

34:                                               ; preds = %18
  store i32 0, ptr %8, align 4
  br label %35

35:                                               ; preds = %41, %34
  %36 = load i32, ptr %8, align 4
  %37 = icmp slt i32 %36, 100
  br i1 %37, label %38, label %44

38:                                               ; preds = %35
  %39 = load i32, ptr %2, align 4
  %40 = add nsw i32 %39, 2
  store i32 %40, ptr %9, align 4
  br label %41

41:                                               ; preds = %38
  %42 = load i32, ptr %8, align 4
  %43 = add nsw i32 %42, 1
  store i32 %43, ptr %8, align 4
  br label %35, !llvm.loop !9

44:                                               ; preds = %35
  br label %45

45:                                               ; preds = %44
  %46 = load i32, ptr %3, align 4
  %47 = add nsw i32 %46, 1
  store i32 %47, ptr %3, align 4
  br label %10, !llvm.loop !10

48:                                               ; preds = %10
  %49 = load i32, ptr %1, align 4
  ret i32 %49
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
