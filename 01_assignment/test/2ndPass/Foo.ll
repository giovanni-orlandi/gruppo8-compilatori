; ModuleID = 'test/2ndPass/Foo.cpp'
source_filename = "test/2ndPass/Foo.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooii(i32 noundef %0, i32 noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  %16 = alloca i32, align 4
  %17 = alloca i32, align 4
  store i32 %0, ptr %3, align 4
  store i32 %1, ptr %4, align 4
  %18 = load i32, ptr %3, align 4
  %19 = mul nsw i32 %18, 16
  store i32 %19, ptr %5, align 4
  %20 = load i32, ptr %4, align 4
  %21 = mul nsw i32 16, %20
  store i32 %21, ptr %6, align 4
  %22 = load i32, ptr %5, align 4
  %23 = mul nsw i32 %22, 17
  store i32 %23, ptr %7, align 4
  %24 = load i32, ptr %6, align 4
  %25 = mul nsw i32 17, %24
  store i32 %25, ptr %8, align 4
  %26 = load i32, ptr %7, align 4
  %27 = mul nsw i32 %26, 15
  store i32 %27, ptr %9, align 4
  %28 = load i32, ptr %8, align 4
  %29 = mul nsw i32 15, %28
  store i32 %29, ptr %10, align 4
  %30 = load i32, ptr %10, align 4
  %31 = sdiv i32 %30, 16
  store i32 %31, ptr %11, align 4
  %32 = load i32, ptr %3, align 4
  %33 = mul nsw i32 -16, %32
  store i32 %33, ptr %12, align 4
  %34 = load i32, ptr %3, align 4
  %35 = sdiv i32 %34, -16
  store i32 %35, ptr %13, align 4
  %36 = load i32, ptr %5, align 4
  %37 = mul nsw i32 %36, 44
  store i32 %37, ptr %14, align 4
  %38 = load i32, ptr %9, align 4
  %39 = sdiv i32 16, %38
  store i32 %39, ptr %15, align 4
  %40 = load i32, ptr %11, align 4
  %41 = sdiv i32 %40, 17
  store i32 %41, ptr %16, align 4
  %42 = load i32, ptr %16, align 4
  %43 = sdiv i32 %42, 15
  store i32 %43, ptr %17, align 4
  %44 = load i32, ptr %13, align 4
  ret i32 %44
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
