; ModuleID = 'test/2ndPass/Foo.m2r.ll'
source_filename = "test/2ndPass/Foo.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooii(i32 noundef %0, i32 noundef %1) #0 {
  %3 = shl i32 %0, 4
  %4 = shl i32 %1, 4
  %5 = shl i32 %3, 4
  %6 = add i32 %5, %3
  %7 = shl i32 %4, 4
  %8 = add i32 %7, %4
  %9 = shl i32 %6, 4
  %10 = sub i32 %9, %6
  %11 = shl i32 %8, 4
  %12 = sub i32 %11, %8
  %13 = ashr i32 %12, 4
  %14 = shl i32 %0, 4
  %15 = sub i32 0, %14
  %16 = ashr i32 %0, 4
  %17 = sub i32 0, %16
  %18 = mul nsw i32 %3, 44
  %19 = sdiv i32 16, %10
  %20 = sdiv i32 %13, 17
  %21 = sdiv i32 %20, 15
  ret i32 %17
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
