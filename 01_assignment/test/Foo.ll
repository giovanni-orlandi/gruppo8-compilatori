; int foo(int e, int a) {
;   int b = a + 1;
;   int c = b * 2;
;   b = e << 1;
;   int d = b / 4;
;   return c - d;
; }

define dso_local i32 @foo(i32 noundef %0, i32 noundef %1) #0 {
  %3 = mul nsw i32 %1, 16
  %4 = sdiv i32 %3, 4
  %5 = mul nsw i32 %1, 17
  %6 = mul nsw i32 %1, 15
  %7 = mul nsw i32 %1, 66

  ret i32 %7
}