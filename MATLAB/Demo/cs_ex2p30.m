% 20150414
% Tim.D. book ex2.30
% explore the time taken by matlab statement r = A(i,:)
% A is m-by-n sparse matrix, i is scalar
% [1] use binary search or linear search ?  --- linear search
% [2] exploit special case e.g. i = 1 and i = m ? --- NO
% why does it NOT exploit special case ? I guess because the
% columns may NOT be sorted.
n = 1000 ;
m = 100 ;
%%%%%%%%%%%%  check binary search  %%%%%%%%%%%%%%
m = 100 : 1000 : 10000 ;
l = length(m) ;
t = zeros(l,1) ;
for j = 1 : l  
  i = int32(m(j) - 1);
  d = rand(m(j), n) ;
  A = sparse(d) ;
  t1 = tic ;
  r = A(i,:) ;
  t2 = toc(t1) ;
  t(j) = t2 ;
end
plot(m, t) ;