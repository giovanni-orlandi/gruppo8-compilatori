; ModuleID = 'test/Foo.ll'
source_filename = "test/Foo.ll"

define dso_local i32 @foo(i32 noundef %0, i32 noundef %1) {
  %3 = shl i32 %1, 4
  %4 = ashr i32 %3, 2
  %5 = shl i32 %1, 4
  %6 = add i32 %5, %1
  %7 = shl i32 %1, 4
  %8 = sub i32 %7, %1
  %9 = mul nsw i32 %1, 104
  ret i32 %9
}
