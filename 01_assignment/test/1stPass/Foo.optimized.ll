; ModuleID = 'test/1stPass/Foo.optimized.bc'
source_filename = "test/1stPass/Foo.ll"

define dso_local i32 @foo(i32 noundef %0, i32 noundef %1) {
  %3 = sub i32 0, %1
  %4 = sdiv i32 1, %0
  ret i32 1
}
