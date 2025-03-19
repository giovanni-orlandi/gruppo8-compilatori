; ModuleID = 'test/Foo.optimized.bc'
source_filename = "test/Foo.ll"

define dso_local i32 @foo(i32 noundef %0, i32 noundef %1) {
  %3 = mul nsw i32 %1, 2
  %4 = shl i32 %0, 1
  %5 = sdiv i32 %4, 4
  %6 = sub nsw i32 0, %5
  ret i32 %6
}
