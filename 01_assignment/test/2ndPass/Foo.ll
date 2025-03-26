define dso_local i32 @foo(i32 noundef %0, i32 noundef %1) #0 {
  %3 = mul i32 %0, 16
  %4 = mul i32 16, %1

  %5 = mul i32 %3, 17
  %6 = mul i32 17, %4

  %7 = mul i32 %5, 15
  %8 = mul i32 15, %6

  %9 = sdiv i32 %8, 16
  %10 = sdiv i32 16, %7

  ret i32 %10
}