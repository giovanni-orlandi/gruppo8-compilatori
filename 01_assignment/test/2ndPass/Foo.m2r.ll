; ModuleID = 'test/2ndPass/Foo.ll'
source_filename = "test/2ndPass/Foo.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooii(i32 noundef %0, i32 noundef %1) #0 {
  %3 = mul nsw i32 %0, 16
  %4 = mul nsw i32 16, %1
  %5 = mul nsw i32 %3, 17
  %6 = mul nsw i32 17, %4
  %7 = mul nsw i32 %5, 15
  %8 = mul nsw i32 15, %6
  %9 = sdiv i32 %8, 16
  %10 = mul nsw i32 -16, %0
  %11 = sdiv i32 %0, -16
  %12 = mul nsw i32 %3, 44
  %13 = sdiv i32 16, %7
  %14 = sdiv i32 %9, 17
  %15 = sdiv i32 %14, 15
  ret i32 %11
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
