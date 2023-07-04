#lang racket
(require compatibility/defmacro)
;function to get the value in matrix by position part 2.

;test 1

(define sudoku1 `((0)))

(define answer1 '((1)))

;test 2

(define sudoku2 `((0 0 0 0) (0 0 0 0) (0 0 0 0) (0 0 0 0)))

(define answer2 '((1 2 3 4) (3 4 1 2) (2 1 4 3) (4 3 2 1)))

;test 3

(define sudoku3 `((0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0)))

(define answer3 '((1 2 3 4 5 6 7 8 9) (4 5 6 7 8 9 1 2 3) (7 8 9 1 2 3 4 5 6) (2 1 4 3 6 5 8 9 7) (3 6 5 8 9 7 2 1 4) (8 9 7 2 1 4 3 6 5) (5 3 1 6 4 2 9 7 8) (6 4 2 9 7 8 5 3 1) (9 7 8 5 3 1 6 4 2)))

;test 4

(define sudoku4 `((0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)))

(define answer4 '((1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16)
                  (5 6 7 8 1 2 3 4 13 14 15 16 9 10 11 12)
                  (9 10 11 12 13 14 15 16 1 2 3 4 5 6 7 8)
                  (13 14 15 16 9 10 11 12 5 6 7 8 1 2 3 4)
                  (2 1 4 3 6 5 8 7 10 9 12 11 14 13 16 15)
                  (6 5 8 7 2 1 4 3 14 13 16 15 10 9 12 11)
                  (10 9 12 11 14 13 16 15 2 1 4 3 6 5 8 7)
                  (14 13 16 15 10 9 12 11 6 5 8 7 2 1 4 3)
                  (3 4 1 2 7 8 5 6 11 12 9 10 15 16 13 14)
                  (7 8 5 6 3 4 1 2 15 16 13 14 11 12 9 10)
                  (11 12 9 10 15 16 13 14 3 4 1 2 7 8 5 6)
                  (15 16 13 14 11 12 9 10 7 8 5 6 3 4 1 2)
                  (4 3 2 1 8 7 6 5 12 11 10 9 16 15 14 13)
                  (8 7 6 5 4 3 2 1 16 15 14 13 12 11 10 9)
                  (12 11 10 9 16 15 14 13 4 3 2 1 8 7 6 5)
                  (16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1)))

;test 5

(define sudoku5 `(
        ( 0 0 5 0 0 8 0 0 0 )
        ( 0 0 0 0 7 0 0 8 0 )
        ( 0 0 0 3 0 0 4 7 5 )
        ( 0 0 0 0 0 7 0 0 0 )
        ( 0 0 0 0 9 4 1 0 0 )
        ( 0 9 0 8 0 0 0 0 0 )
        ( 9 2 0 0 0 0 0 3 8 )
        ( 1 0 0 0 0 6 0 0 9 )
        ( 3 4 0 0 0 2 6 0 0 )
  ))

(define answer5 '((7 3 5 2 4 8 9 1 6) (4 6 9 1 7 5 3 8 2) (2 8 1 3 6 9 4 7 5) (5 1 3 6 2 7 8 9 4) (8 7 2 5 9 4 1 6 3) (6 9 4 8 1 3 5 2 7) (9 2 6 4 5 1 7 3 8) (1 5 8 7 3 6 2 4 9) (3 4 7 9 8 2 6 5 1)))

;test 6

(define sudoku6 `(
        ( 6 0 2 0 0 1 0 0 4 )
        ( 0 0 0 0 6 0 0 0 0 )
        ( 0 4 0 0 8 7 1 0 0 )
        ( 1 5 7 0 4 0 0 8 2 )
        ( 0 0 6 0 2 0 4 7 0 )
        ( 0 8 0 0 0 0 0 0 0 )
        ( 0 0 5 0 0 2 0 0 0 )
        ( 0 0 0 0 1 0 2 4 0 )
        ( 0 0 0 0 3 0 6 0 1 )
  ))

(define answer6 '((6 7 2 3 5 1 8 9 4) (8 3 1 4 6 9 5 2 7) (5 4 9 2 8 7 1 6 3) (1 5 7 9 4 6 3 8 2) (3 9 6 1 2 8 4 7 5) (2 8 4 5 7 3 9 1 6) (4 1 5 6 9 2 7 3 8) (7 6 3 8 1 5 2 4 9) (9 2 8 7 3 4 6 5 1)))

;test 7

(define sudoku7 `(
        ( 9 0 0 3 0 0 0 0 0 )
        ( 2 0 5 0 0 1 6 0 0 )
        ( 0 0 0 0 6 0 0 4 0 )
        ( 0 0 0 7 0 0 0 0 3 )
        ( 6 0 1 0 0 2 4 0 0 )
        ( 0 8 0 0 0 0 0 0 0 )
        ( 0 9 0 0 0 0 5 0 0 )
        ( 0 4 0 0 0 8 0 0 0 )
        ( 5 0 8 2 0 0 0 7 0 )
  ))


(define answer7 '((9 6 4 3 2 7 1 5 8) (2 7 5 4 8 1 6 3 9) (8 1 3 9 6 5 7 4 2) (4 2 9 7 5 6 8 1 3) (6 5 1 8 3 2 4 9 7) (3 8 7 1 4 9 2 6 5) (1 9 2 6 7 3 5 8 4) (7 4 6 5 9 8 3 2 1) (5 3 8 2 1 4 9 7 6)))

;test 8

(define sudoku8 `(
        ( 9 9 0 3 0 0 0 0 0 )
        ( 2 0 5 0 0 1 6 0 0 )
        ( 0 0 0 0 6 0 0 4 0 )
        ( 0 0 0 7 0 0 0 0 3 )
        ( 6 0 1 0 0 2 4 0 0 )
        ( 0 8 0 0 0 0 0 0 0 )
        ( 0 9 0 0 0 0 5 0 0 )
        ( 0 4 0 0 0 8 0 0 0 )
        ( 5 0 8 2 0 0 0 7 0 )
  ))

(define answer8 #f)

;test 9

(define sudoku9 `((11 0 6 4 7 12 0 0 5 1 0 9 2 0 0 8)
   (2 8 0 1 3 4 0 10 0 7 12 0 0 9 6 5) 
   (13 15 0 16 9 0 1 8 0 2 3 6 0 12 7 4)
   (5 0 7 9 2 0 15 6 4 8 0 14 1 3 0 13) 
   (1 14 0 8 6 0 9 2 12 0 0 11 4 16 10 7) 
   (12 0 9 5 13 14 3 11 16 6 4 7 15 2 8 1)
   (15 7 2 11 0 0 12 0 0 14 0 0 5 6 9 3) 
   (6 16 4 3 5 7 10 1 8 9 2 15 12 11 0 14) 
   (8 4 3 14 10 1 13 9 7 16 6 12 11 15 5 2) 
   (9 1 11 2 0 0 4 0 0 5 0 0 13 14 12 6) 
   (0 0 12 13 0 0 0 14 3 0 0 0 7 8 0 0) 
   (7 5 0 15 11 0 8 0 0 13 0 2 3 0 4 10) 
   (0 0 1 7 12 0 6 0 0 15 0 4 8 13 0 0) 
   (14 0 0 0 8 13 16 0 0 10 7 5 0 0 0 12) 
   (0 2 0 12 1 0 0 0 0 0 0 3 10 0 14 0) 
   (0 13 5 10 0 11 0 0 0 0 8 0 6 7 1 0)))

(define answer9 '((11 3 6 4 7 12 14 13 5 1 16 9 2 10 15 8)
  (2 8 14 1 3 4 11 10 15 7 12 13 16 9 6 5)
  (13 15 10 16 9 5 1 8 11 2 3 6 14 12 7 4)
  (5 12 7 9 2 16 15 6 4 8 10 14 1 3 11 13)
  (1 14 13 8 6 15 9 2 12 3 5 11 4 16 10 7)
  (12 10 9 5 13 14 3 11 16 6 4 7 15 2 8 1)
  (15 7 2 11 4 8 12 16 13 14 1 10 5 6 9 3)
  (6 16 4 3 5 7 10 1 8 9 2 15 12 11 13 14)
  (8 4 3 14 10 1 13 9 7 16 6 12 11 15 5 2)
  (9 1 11 2 16 3 4 7 10 5 15 8 13 14 12 6)
  (10 6 12 13 15 2 5 14 3 4 11 1 7 8 16 9)
  (7 5 16 15 11 6 8 12 14 13 9 2 3 1 4 10)
  (16 9 1 7 12 10 6 5 2 15 14 4 8 13 3 11)
  (14 11 15 6 8 13 16 3 1 10 7 5 9 4 2 12)
  (4 2 8 12 1 9 7 15 6 11 13 3 10 5 14 16)
  (3 13 5 10 14 11 2 4 9 12 8 16 6 7 1 15)))

(define (get-pos-x x y mat)
	(if (> x 1)
		(get-pos-x (- x 1) y (cdr mat))
		(car mat)
))

;function to get the value in matrix by position part 1.
(define (get-pos x y mat)
	(if (> y 1)
		(get-pos x (- y 1) (cdr mat))
		(get-pos-x x y (car mat)))
) 

;function to check if the number safe in a row part 2.
(define (check-row-x elem x i row)
  (if (null? row)
      true
      (if (and (= elem (car row)) (not (= x i)))
          false
          (check-row-x elem x (+ i 1) (cdr row)))))

;function to check if the number safe in a row part 1.
(define (check-row elem x y mat)
  (if (> y 1)
      (check-row elem x (- y 1) (cdr mat))
      (check-row-x elem x 1 (car mat))))

;function to check if the number safe in a column
(define (check-col elem x y i mat size)
  (if (> i size)
      true
      (if (and (= elem (get-pos x i mat)) (not (= i y)))
         false
         (check-col elem x y (+ i 1) mat size))))

;function to round a number
(define (round x i)
  (if (<= x i)
      i
      (round x (+ i 1))))

;function to find define in what sudoku square is number
(define (def-sqr size y)
  (round (/ y size) 1))

;function to check if the number is safe to insert in square part 3.
(define (check-square elem x0 y0 x y numx numy mat size)
  (if (< x (+ size 1))
      (if (and (= elem (get-pos (+ x (* size numx)) (+ y (* size numy)) mat)) (not (and (= x0 (+ x (* size numx))) (= y0 (+ y (* size numy))))))
          false
          (check-square elem x0 y0 (+ 1 x) y numx numy mat size))
      (if(< y size)
          (check-square elem x0 y0 1 (+ y 1) numx numy mat size)
          true)))

;function to check if the number is safe to insert in square part 2.
(define (check-sq-x elem x y numy mat size)
  (check-square elem x y 1 1 ( - (def-sqr size x) 1) numy mat size))

;function to check if the number is safe to insert in square part 1.
(define ( check-sq elem x y mat size)
    (check-sq-x elem x y (- (def-sqr size y) 1) mat size))

;function to find a square of number
(define (ppa-square x i)
  (if (= x (* i i))
      i
      (ppa-square x (+ i 1))))

;function to check if the number is safe to insert by position.
(define (ppa-check mat x y elem size)
      (if (check-row elem x y mat)
          (if (check-col elem x y 1 mat (* size size))
              (if (check-sq elem x y mat size )
                  true
                  false)
              false)
          false))
;function to find position of the closest empty cell("0" in our case) in sudoku part 2.
(define (find-zero-row mat x y)
  (if (null? mat)
      false
      (if (= (car mat) 0)
          (cons y x)
          (find-zero-row (cdr mat) (+ x 1) y))))

;function to find position of the closest empty cell("0" in our case) in sudoku part 1.
(define (find-zero mat x y)
  (if (null? mat)
      false
      (let ([coord (find-zero-row (car mat) x y)])
        (if (not (boolean? coord))
            coord
            (find-zero (cdr mat) 0 (+ y 1))))))
        

;function to replace an element by position in sudoku(matrix) part 2.
(define (replace-inner row x elem)
  (if (> x 1)
      (cons (car row) (replace-inner (cdr row) (- x 1) elem))
      (cons elem (cdr row))))

;function to replace an element by position in sudoku(matrix) part 1.
(define (replace mat x y elem)
  (if (> y 1)
      (cons (car mat) (replace (cdr mat) x (- y 1) elem))
      (cons (replace-inner (car mat) x elem) (cdr mat))))
  
;function that solves our sudoku by backtracking
(define (findsolution mat elem size)
  (if (< elem (+ (* size size) 1))
  (let ([indexes (find-zero mat 0 0)])  ;indexes have coordinates of position in format `(y.x)
    (if (boolean? indexes)   ;if there is no zeroes, than we have an answer
        mat
        (let ([y (+ (car indexes) 1)])   ;writes the coordinates
          (let ([x (+ (cdr indexes) 1)])  ;writes the coordinates
           (if (ppa-check mat x y elem size)   ;here function checks is it safe to insert element
               (let ([answer (findsolution (replace mat x y elem) 1 size) ]) ;trying to find answer
                 (if (not (boolean? answer))   ; if the return is false(bool), then try another solution, otherwise we have an answer
                     answer
                     (findsolution mat (+ elem 1) size)))
                 (findsolution mat (+ elem 1) size))))))
  false))  ;if nothing worked, then there is no solution, return false

;function to find the size of sudoku
(define (ppa-size mat size)
  (if (null? mat)
      size
      (ppa-size (cdr mat) (+ size 1))))

;function to control if the row of sudoku is valid
(define (valid-row? row x y check size)
  (if (null? row)
      true
      (if (= (car row) 0)
          (valid-row? (cdr row) (+ x 1) y check size)
          (if (ppa-check check x y (car row) size)
              (valid-row? (cdr row) (+ x 1) y check size)
              false))))

;function to control if the sudoku is valid
(define (valid? mat x y check size)
  (if (null? mat)
      true
      (if (valid-row? (car mat) x y check size)
          (valid? (cdr mat) x (+ y 1) check size)
          false)))

;if sudoku is valid, then try to solve it
(define (solve-sudoku mat)
  (let ([ size (ppa-square (ppa-size mat 0) 1)])
    (if (valid? mat 1 1 mat size)
        (findsolution mat 1 size)
        false)))

(define-macro (aux-assert expr) expr)

(define-macro (assert-equal sudoku answer)
  `(unless (aux-assert (equal? ,sudoku ,answer))
       (error (format "Failed assertion (L~a): '(assert-equal ~a ~a)'\n lhs: ~a\n rhs: ~a" (syntax-line #'here) ',sudoku ',answer ,sudoku ,answer))))

(assert-equal (solve-sudoku sudoku1) answer1)
(assert-equal (solve-sudoku sudoku2) answer2)
(assert-equal (solve-sudoku sudoku3) answer3)
(assert-equal (solve-sudoku sudoku4) answer4)
(assert-equal (solve-sudoku sudoku5) answer5)
(assert-equal (solve-sudoku sudoku6) answer6)
(assert-equal (solve-sudoku sudoku7) answer7)
(assert-equal (solve-sudoku sudoku8) answer8)
(assert-equal (solve-sudoku sudoku9) answer9)