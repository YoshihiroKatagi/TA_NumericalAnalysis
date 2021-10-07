program main
​
 !課題2-1
 implicit none
 real a,b,h,n,S
 
 print *,'tyuutensoku_verification'       !中点則の検証
 print *,'n              result'
​
 do n = 1,20    !n=分割数
​
  a = 0e0       !積分範囲の下限値
  b = 5e0       !積分範囲の上限値
 
  S = 0e0
 
 call tyuutensoku(a,b,S,n)
​
 write(*,*),n,S
​
 end do
​
 print *,'daikeisoku_verification'       !台形則の検証
 print *,'n              result'
​
 do n = 1,20    !n=分割数
​
  a = 0e0       !積分範囲の下限値
  b = 5e0       !積分範囲の上限値
  h = b/n				!刻み幅
 
  S = 0e0
 
 call daikei(a,b,S,h)
​
 write(*,*),n,S
​
 end do
​
 print *,'simpsonsoku_verification'       !シンプソン則の検証
 print *,'n              result'
​
 do n = 1,20    !n=分割数
​
  a = 0e0       !積分範囲の下限値
  b = 5e0       !積分範囲の上限値
  h = b/n				!刻み幅
 
  S = 0e0
 
  call sympson(a,b,S,h)
​
 write(*,*),n,S
​
 end do
​
end program main
​
subroutine tyuutensoku(a,b,S,n)
​
  implicit none
  integer i
  real a,b,S,n,h,x
​
  h = (b - a) / n 
​
  do i = 0,n
​
     x = a + h*(2*i + 1)/2
     S = S + 2**x
  
  end do
​
  S = S*h
​
end subroutine tyuutensoku
​
subroutine daikei(a,b,S,h)
​
 implicit none
 integer i
 real a,b,S,h,x1,x2,y1,y2
​
  x1 = a
  x2 = a + h
  
  do i = a+1,b/h
  
    y1 = 2**x1
    y2 = 2**x2
  
    S = S + h*(y1+y2)/2
  
    x1 = x2
    x2 = x2 + h
  
  enddo
​
end subroutine daikei
​
subroutine sympson(a,b,S,h)
​
  implicit none
  integer i
  real a,b,S,h,x1,x2,x3,y1,y2,y3
 
   x1 = a
   x2 = a + h/2
   x3 = a + h
  
   do i = a+1,b/h
   
    y1 = 2**x1
    y2 = 2**x2
    y3 = 2**x3
​
    S = S + h*(y1+4*y2+y3)/6
  
    x1 = x1 + h
    x2 = x2 + h
    x3 = x3 + h
  
   enddo
 
 end subroutine sympson