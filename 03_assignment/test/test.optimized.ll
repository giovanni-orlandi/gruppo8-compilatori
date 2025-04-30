; ModuleID = 'test/test.m2r.ll'
source_filename = "test/test.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooiiii(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) #0 {
  %5 = add nsw i32 %0, %1
  %6 = sdiv i32 %5, 2
  %7 = add nsw i32 %5, 310
  %8 = add nsw i32 undef, 3
  br label %9

9:                                                ; preds = %17, %4
  %.0 = phi i32 [ 0, %4 ], [ %10, %17 ]
  %10 = add nsw i32 %.0, 1
  %11 = icmp slt i32 %3, 10
  br i1 %11, label %12, label %16

12:                                               ; preds = %9
  %13 = icmp slt i32 %1, 5
  br i1 %13, label %14, label %15

14:                                               ; preds = %12
  br label %18

15:                                               ; preds = %12
  br label %17

16:                                               ; preds = %9
  br label %17

17:                                               ; preds = %16, %15
  br label %9, !llvm.loop !6

18:                                               ; preds = %14
  call void @llvm.trap()
  unreachable
}

; Function Attrs: cold noreturn nounwind memory(inaccessiblemem: write)
declare void @llvm.trap() #1

attributes #0 = { mustprogress noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { cold noreturn nounwind memory(inaccessiblemem: write) }

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
