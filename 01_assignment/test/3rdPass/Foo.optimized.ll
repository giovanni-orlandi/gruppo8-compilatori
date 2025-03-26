; ModuleID = 'test/Foo.optimized.bc'
source_filename = "test/Foo.ll"

define dso_local i32 @foo(i32 noundef %0, i32 noundef %1) {
  %3 = sub i32 %0, 16
  %4 = mul i32 16, %1
  %5 = add i32 %3, 16
  %6 = mul i32 17, %4
  %7 = mul i32 %0, 15
  %8 = mul i32 15, %6
  %9 = sdiv i32 %8, 16
  %10 = sdiv i32 16, %7
  ret i32 %10
}
