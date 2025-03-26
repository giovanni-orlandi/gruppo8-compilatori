; ModuleID = 'test/2ndPass/Foo.ll'
source_filename = "test/2ndPass/Foo.ll"

define dso_local i32 @foo(i32 noundef %0, i32 noundef %1) {
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
  %14 = sdiv i32 16, %10
  ret i32 %14
}
