; ModuleID = 'test/rotated/vectors.ll'
source_filename = "test/rotated/vectors.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [13 x i8] c"EHIIIII: %d\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local void @test_arrays(i32 noundef %0) #0 {
  %2 = mul nsw i32 2, %0
  %3 = zext i32 %2 to i64
  %4 = call ptr @llvm.stacksave.p0()
  %5 = alloca i32, i64 %3, align 16
  br label %6

6:                                                ; preds = %11, %1
  %.01 = phi i32 [ 0, %1 ], [ %12, %11 ]
  %7 = icmp slt i32 %.01, %0
  br i1 %7, label %8, label %13

8:                                                ; preds = %6
  %9 = sext i32 %.01 to i64
  %10 = getelementptr inbounds i32, ptr %5, i64 %9
  store i32 %.01, ptr %10, align 4
  br label %11

11:                                               ; preds = %8
  %12 = add nsw i32 %.01, 1
  br label %6, !llvm.loop !6

13:                                               ; preds = %6
  br label %14

14:                                               ; preds = %22, %13
  %.1 = phi i32 [ 0, %13 ], [ %23, %22 ]
  %.0 = phi i32 [ 0, %13 ], [ %21, %22 ]
  %15 = icmp slt i32 %.1, %0
  br i1 %15, label %16, label %24

16:                                               ; preds = %14
  %17 = add nsw i32 %.1, 1
  %18 = sext i32 %17 to i64
  %19 = getelementptr inbounds i32, ptr %5, i64 %18
  %20 = load i32, ptr %19, align 4
  %21 = add nsw i32 %.0, %20
  br label %22

22:                                               ; preds = %16
  %23 = add nsw i32 %.1, 1
  br label %14, !llvm.loop !8

24:                                               ; preds = %14
  %25 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %.0)
  call void @llvm.stackrestore.p0(ptr %4)
  ret void
}

; Function Attrs: nocallback nofree nosync nounwind willreturn
declare ptr @llvm.stacksave.p0() #1

declare i32 @printf(ptr noundef, ...) #2

; Function Attrs: nocallback nofree nosync nounwind willreturn
declare void @llvm.stackrestore.p0(ptr) #1

; Function Attrs: noinline nounwind uwtable
define dso_local void @main() #0 {
  call void @test_arrays(i32 noundef 4)
  ret void
}

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind willreturn }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

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
