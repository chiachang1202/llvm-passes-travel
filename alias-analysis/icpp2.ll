; ModuleID = 'icpp2.c'
source_filename = "icpp2.c"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

; Function Attrs: noinline nounwind ssp uwtable
define void @icpp() #0 {
entry:
  %x = alloca i32, align 4
  %y = alloca i32, align 4
  %p = alloca i32*, align 8
  %pp = alloca i32**, align 8
  store i32* %x, i32** %p, align 8
  store i32** %p, i32*** %pp, align 8
  %0 = load i32**, i32*** %pp, align 8
  store i32* %y, i32** %0, align 8
  %1 = load i32*, i32** %p, align 8
  store i32 3, i32* %1, align 4
  %2 = load i32*, i32** %p, align 8
  %3 = load i32, i32* %2, align 4
  %4 = load i32**, i32*** %pp, align 8
  %5 = load i32*, i32** %4, align 8
  store i32 %3, i32* %5, align 4
  ret void
}

attributes #0 = { noinline nounwind ssp uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"uwtable", i32 1}
!3 = !{i32 7, !"frame-pointer", i32 2}
!4 = !{!"Homebrew clang version 13.0.0"}
