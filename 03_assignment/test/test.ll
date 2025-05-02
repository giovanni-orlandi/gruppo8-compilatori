; ModuleID = 'test/test.cpp'
source_filename = "test/test.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z4foo1ii(i32 noundef %0, i32 noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store i32 %0, ptr %3, align 4
  store i32 %1, ptr %4, align 4
  br label %7

7:                                                ; preds = %2, %13
  %8 = load i32, ptr %4, align 4
  %9 = add nsw i32 1, %8
  store i32 %9, ptr %5, align 4
  %10 = load i32, ptr %3, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %12, label %13

12:                                               ; preds = %7
  br label %16

13:                                               ; preds = %7
  %14 = load i32, ptr %3, align 4
  %15 = add nsw i32 %14, -1
  store i32 %15, ptr %3, align 4
  br label %7, !llvm.loop !6

16:                                               ; preds = %12
  %17 = load i32, ptr %5, align 4
  %18 = add nsw i32 %17, 2
  store i32 %18, ptr %6, align 4
  ret i32 0
}

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z4foo2ii(i32 noundef %0, i32 noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i32 %0, ptr %3, align 4
  store i32 %1, ptr %4, align 4
  store i32 0, ptr %6, align 4
  br label %8

8:                                                ; preds = %14, %2
  %9 = load i32, ptr %6, align 4
  %10 = icmp slt i32 %9, 10
  br i1 %10, label %11, label %17

11:                                               ; preds = %8
  %12 = load i32, ptr %4, align 4
  %13 = add nsw i32 1, %12
  store i32 %13, ptr %5, align 4
  br label %14

14:                                               ; preds = %11
  %15 = load i32, ptr %6, align 4
  %16 = add nsw i32 %15, 1
  store i32 %16, ptr %6, align 4
  br label %8, !llvm.loop !8

17:                                               ; preds = %8
  %18 = load i32, ptr %5, align 4
  %19 = add nsw i32 %18, 2
  store i32 %19, ptr %7, align 4
  ret i32 0
}

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z4foo3ii(i32 noundef %0, i32 noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store i32 %0, ptr %3, align 4
  store i32 %1, ptr %4, align 4
  store i32 0, ptr %6, align 4
  br label %7

7:                                                ; preds = %13, %2
  %8 = load i32, ptr %6, align 4
  %9 = icmp slt i32 %8, 10
  br i1 %9, label %10, label %16

10:                                               ; preds = %7
  %11 = load i32, ptr %4, align 4
  %12 = add nsw i32 1, %11
  store i32 %12, ptr %5, align 4
  br label %13

13:                                               ; preds = %10
  %14 = load i32, ptr %6, align 4
  %15 = add nsw i32 %14, 1
  store i32 %15, ptr %6, align 4
  br label %7, !llvm.loop !9

16:                                               ; preds = %7
  ret i32 0
}

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z4foo4ii(i32 noundef %0, i32 noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i32 %0, ptr %3, align 4
  store i32 %1, ptr %4, align 4
  br label %6

6:                                                ; preds = %2, %21
  %7 = load i32, ptr %3, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %9, label %10

9:                                                ; preds = %6
  br label %24

10:                                               ; preds = %6
  br label %11

11:                                               ; preds = %10, %17
  %12 = load i32, ptr %3, align 4
  %13 = add nsw i32 1, %12
  store i32 %13, ptr %5, align 4
  %14 = load i32, ptr %4, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %16, label %17

16:                                               ; preds = %11
  br label %20

17:                                               ; preds = %11
  %18 = load i32, ptr %4, align 4
  %19 = add nsw i32 %18, -1
  store i32 %19, ptr %4, align 4
  br label %11, !llvm.loop !10

20:                                               ; preds = %16
  br label %21

21:                                               ; preds = %20
  %22 = load i32, ptr %3, align 4
  %23 = add nsw i32 %22, -1
  store i32 %23, ptr %3, align 4
  br label %6, !llvm.loop !11

24:                                               ; preds = %9
  ret i32 0
}

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z4foo5iii(i32 noundef %0, i32 noundef %1, i32 noundef %2) #0 {
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i32 %0, ptr %4, align 4
  store i32 %1, ptr %5, align 4
  store i32 %2, ptr %6, align 4
  br label %8

8:                                                ; preds = %3, %23
  %9 = load i32, ptr %4, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %11, label %12

11:                                               ; preds = %8
  br label %26

12:                                               ; preds = %8
  br label %13

13:                                               ; preds = %12, %19
  %14 = load i32, ptr %6, align 4
  %15 = add nsw i32 1, %14
  store i32 %15, ptr %7, align 4
  %16 = load i32, ptr %5, align 4
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %18, label %19

18:                                               ; preds = %13
  br label %22

19:                                               ; preds = %13
  %20 = load i32, ptr %5, align 4
  %21 = add nsw i32 %20, -1
  store i32 %21, ptr %5, align 4
  br label %13, !llvm.loop !12

22:                                               ; preds = %18
  br label %23

23:                                               ; preds = %22
  %24 = load i32, ptr %4, align 4
  %25 = add nsw i32 %24, -1
  store i32 %25, ptr %4, align 4
  br label %8, !llvm.loop !13

26:                                               ; preds = %11
  ret i32 0
}

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z4foo6iiii(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) #0 {
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  store i32 %0, ptr %5, align 4
  store i32 %1, ptr %6, align 4
  store i32 %2, ptr %7, align 4
  store i32 %3, ptr %8, align 4
  br label %12

12:                                               ; preds = %4, %49
  %13 = load i32, ptr %5, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %15, label %16

15:                                               ; preds = %12
  br label %52

16:                                               ; preds = %12
  br label %17

17:                                               ; preds = %16, %45
  %18 = load i32, ptr %5, align 4
  %19 = add nsw i32 %18, 1
  store i32 %19, ptr %9, align 4
  %20 = load i32, ptr %6, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %22, label %23

22:                                               ; preds = %17
  br label %48

23:                                               ; preds = %17
  br label %24

24:                                               ; preds = %23, %41
  %25 = load i32, ptr %6, align 4
  %26 = add nsw i32 %25, 2
  store i32 %26, ptr %10, align 4
  %27 = load i32, ptr %7, align 4
  %28 = icmp eq i32 %27, 0
  br i1 %28, label %29, label %30

29:                                               ; preds = %24
  br label %44

30:                                               ; preds = %24
  br label %31

31:                                               ; preds = %30, %37
  %32 = load i32, ptr %7, align 4
  %33 = add nsw i32 %32, 3
  store i32 %33, ptr %11, align 4
  %34 = load i32, ptr %8, align 4
  %35 = icmp eq i32 %34, 0
  br i1 %35, label %36, label %37

36:                                               ; preds = %31
  br label %40

37:                                               ; preds = %31
  %38 = load i32, ptr %8, align 4
  %39 = add nsw i32 %38, -1
  store i32 %39, ptr %8, align 4
  br label %31, !llvm.loop !14

40:                                               ; preds = %36
  br label %41

41:                                               ; preds = %40
  %42 = load i32, ptr %7, align 4
  %43 = add nsw i32 %42, -1
  store i32 %43, ptr %7, align 4
  br label %24, !llvm.loop !15

44:                                               ; preds = %29
  br label %45

45:                                               ; preds = %44
  %46 = load i32, ptr %6, align 4
  %47 = add nsw i32 %46, -1
  store i32 %47, ptr %6, align 4
  br label %17, !llvm.loop !16

48:                                               ; preds = %22
  br label %49

49:                                               ; preds = %48
  %50 = load i32, ptr %5, align 4
  %51 = add nsw i32 %50, -1
  store i32 %51, ptr %5, align 4
  br label %12, !llvm.loop !17

52:                                               ; preds = %15
  call void @llvm.trap()
  unreachable
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
!11 = distinct !{!11, !7}
!12 = distinct !{!12, !7}
!13 = distinct !{!13, !7}
!14 = distinct !{!14, !7}
!15 = distinct !{!15, !7}
!16 = distinct !{!16, !7}
!17 = distinct !{!17, !7}
