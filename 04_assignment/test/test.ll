; ModuleID = 'test/test.c'
source_filename = "test/test.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [11 x i8] c"Somma: %d\0A\00", align 1
@.str.1 = private unnamed_addr constant [14 x i8] c"Prodotto: %d\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local void @test(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i32 %0, ptr %2, align 4
  store i32 0, ptr %3, align 4
  store i32 0, ptr %4, align 4
  store i32 1, ptr %5, align 4
  br label %6

6:                                                ; preds = %12, %1
  %7 = load i32, ptr %3, align 4
  %8 = add nsw i32 %7, 1
  store i32 %8, ptr %3, align 4
  %9 = load i32, ptr %3, align 4
  %10 = load i32, ptr %4, align 4
  %11 = add nsw i32 %10, %9
  store i32 %11, ptr %4, align 4
  br label %12

12:                                               ; preds = %6
  %13 = load i32, ptr %3, align 4
  %14 = load i32, ptr %2, align 4
  %15 = icmp slt i32 %13, %14
  br i1 %15, label %6, label %16, !llvm.loop !6

16:                                               ; preds = %12
  store i32 0, ptr %3, align 4
  br label %17

17:                                               ; preds = %24, %16
  %18 = load i32, ptr %3, align 4
  %19 = add nsw i32 %18, 1
  %20 = load i32, ptr %5, align 4
  %21 = mul nsw i32 %20, %19
  store i32 %21, ptr %5, align 4
  %22 = load i32, ptr %3, align 4
  %23 = add nsw i32 %22, 1
  store i32 %23, ptr %3, align 4
  br label %24

24:                                               ; preds = %17
  %25 = load i32, ptr %3, align 4
  %26 = load i32, ptr %2, align 4
  %27 = icmp slt i32 %25, %26
  br i1 %27, label %17, label %28, !llvm.loop !8

28:                                               ; preds = %24
  %29 = load i32, ptr %4, align 4
  %30 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %29)
  %31 = load i32, ptr %5, align 4
  %32 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %31)
  ret void
}

declare i32 @printf(ptr noundef, ...) #1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  store i32 5, ptr %2, align 4
  %3 = load i32, ptr %2, align 4
  call void @test(i32 noundef %3)
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
!8 = distinct !{!8, !7}
