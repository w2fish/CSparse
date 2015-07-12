% read matrix from file, solve Lx=b
% compare with cs_lsolvesp
n = 11;
nzmax = 33;
bnonzero = 4;
L = zeros(n);
fp = fopen('fileMatrix', 'r'); 
t = fscanf(fp, '%d%d%d');
t = reshape(t, 3, nzmax);
for i = 1 : nzmax
  L(t(1,i)+1, t(2,i)+1) = t(3,i);
end
fclose(fp);
b = zeros(n,1);
fp = fopen('fileVectorX', 'r');
t = fscanf(fp, '%d%d%d');
t = reshape(t, 3, bnonzero);
for i = 1 : bnonzero
  b(t(1,i)+1, t(2,i)+1) = t(3,i);
end
fclose(fp);
x = L \ b;
b'
x'