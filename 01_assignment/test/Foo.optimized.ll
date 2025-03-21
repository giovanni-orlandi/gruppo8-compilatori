; ModuleID = 'test/Foo.optimized.bc'
source_filename = "test/Foo.ll"

define dso_local i32 @foo(i32 noundef %0, i32 noundef %1) {
  %3 = add nsw i32 %1, 0
  %4 = mul nsw i32 %3, 16
  %5 = shl i32 %3, 4
  %6 = shl i32 %0, 1
  %7 = sdiv i32 %6, 4
  %8 = ashr i32 %6, 2
  %9 = sub nsw i32 0, %8
  ret i32 %9
}
