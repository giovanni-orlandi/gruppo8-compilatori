; ModuleID = 'test/test.m2r.ll'
source_filename = "test/test.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind uwtable
define dso_local void @testarray(i32 noundef %0) #0 {
  %2 = mul nsw i32 2, %0
  %3 = zext i32 %2 to i64
  %4 = call ptr @llvm.stacksave.p0()
  %5 = alloca i32, i64 %3, align 16
  %6 = mul nsw i32 2, %0
  %7 = zext i32 %6 to i64
  %8 = alloca i32, i64 %7, align 16
  br label %9

9:                                                ; preds = %13, %1
  %.01 = phi i32 [ 0, %1 ], [ %10, %13 ]
  %10 = add nsw i32 %.01, 1
  %11 = sext i32 %10 to i64
  %12 = getelementptr inbounds i32, ptr %5, i64 %11
  store i32 3, ptr %12, align 4
  br label %13

13:                                               ; preds = %9
  %14 = icmp slt i32 %10, %0
  br i1 %14, label %9, label %15, !llvm.loop !6

15:                                               ; preds = %13
  br label %16

16:                                               ; preds = %25, %15
  %.1 = phi i32 [ 0, %15 ], [ %24, %25 ]
  %.0 = phi i32 [ 0, %15 ], [ %23, %25 ]
  %17 = mul nsw i32 %.0, 4
  %18 = sext i32 %17 to i64
  %19 = getelementptr inbounds i32, ptr %5, i64 %18
  %20 = load i32, ptr %19, align 4
  %21 = sext i32 %.1 to i64
  %22 = getelementptr inbounds i32, ptr %8, i64 %21
  store i32 %20, ptr %22, align 4
  %23 = add nsw i32 %.0, 2
  %24 = add nsw i32 %.1, 1
  br label %25

25:                                               ; preds = %16
  %26 = icmp slt i32 %24, %0
  br i1 %26, label %16, label %27, !llvm.loop !8

27:                                               ; preds = %25
  call void @llvm.stackrestore.p0(ptr %4)
  ret void
}

; Function Attrs: nocallback nofree nosync nounwind willreturn
declare ptr @llvm.stacksave.p0() #1

; Function Attrs: nocallback nofree nosync nounwind willreturn
declare void @llvm.stackrestore.p0(ptr) #1

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind willreturn }

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
