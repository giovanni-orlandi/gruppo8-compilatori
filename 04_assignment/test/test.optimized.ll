; ModuleID = 'test/test.m2r.ll'
source_filename = "test/test.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [11 x i8] c"Somma: %d\0A\00", align 1
@.str.1 = private unnamed_addr constant [14 x i8] c"Prodotto: %d\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local void @test_arr(i32 noundef %0) #0 {
  %2 = mul nsw i32 2, %0
  %3 = zext i32 %2 to i64
  %4 = call ptr @llvm.stacksave.p0()
  %5 = alloca i32, i64 %3, align 16
  br label %6

6:                                                ; preds = %11, %1
  %.02 = phi i32 [ 0, %1 ], [ %10, %11 ]
  %.01 = phi i32 [ 0, %1 ], [ %9, %11 ]
  %7 = sext i32 %.01 to i64
  %8 = getelementptr inbounds i32, ptr %5, i64 %7
  store i32 %.01, ptr %8, align 4
  %9 = add nsw i32 %.01, 1
  %10 = add nsw i32 %.02, %9
  br label %11

11:                                               ; preds = %6
  %12 = icmp slt i32 %9, %0
  br i1 %12, label %6, label %13, !llvm.loop !6

13:                                               ; preds = %11
  br label %14

14:                                               ; preds = %22, %13
  %.1 = phi i32 [ 0, %13 ], [ %21, %22 ]
  %.0 = phi i32 [ 1, %13 ], [ %20, %22 ]
  %15 = add nsw i32 %.1, 1
  %16 = sext i32 %15 to i64
  %17 = getelementptr inbounds i32, ptr %5, i64 %16
  %18 = load i32, ptr %17, align 4
  %19 = add nsw i32 %.1, 3
  %20 = mul nsw i32 %.0, %19
  %21 = add nsw i32 %.1, 1
  br label %22

22:                                               ; preds = %14
  %23 = icmp slt i32 %21, %0
  br i1 %23, label %14, label %24, !llvm.loop !8

24:                                               ; preds = %22
  %25 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %18)
  %26 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %20)
  call void @llvm.stackrestore.p0(ptr %4)
  ret void
}

; Function Attrs: nocallback nofree nosync nounwind willreturn
declare ptr @llvm.stacksave.p0() #1

declare i32 @printf(ptr noundef, ...) #2

; Function Attrs: nocallback nofree nosync nounwind willreturn
declare void @llvm.stackrestore.p0(ptr) #1

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
