;; Test that the binary encoding of the dump matches that of the original
;; RUN: sexpr_dump %s > %t1
;; RUN: sexpr-wasm -d %t1 > %t2
;; RUN: sexpr-wasm -d %s | diff - %t2
;; Test that round-tripping is stable
;; RUN: sexpr_dump %t1 | diff %t1 -
(module
  (func
    (i32.load align=4 (i32.const 0))
    (i64.load align=4 (i32.const 0))
    (i64.load8_s align=8 (i32.const 0))
    (i64.load16_s align=1 (i32.const 0))
    (i64.load32_s align=2 (i32.const 0))
    (i64.load8_u align=4 (i32.const 0))
    (i64.load16_u align=8 (i32.const 0))
    (i64.load32_u align=1 (i32.const 0))
    (i32.load8_s align=8 (i32.const 0))
    (i32.load16_s align=1 (i32.const 0))
    (i32.load8_u align=4 (i32.const 0))
    (i32.load16_u align=8 (i32.const 0))
    (f32.load align=2 (i32.const 0))
    (f64.load align=8 (i32.const 0))))
