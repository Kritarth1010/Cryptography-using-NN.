clear all;
close all;
clc;
inp=input('What message would u like to encrypt:');
inp=double(inp);
for i=1:length(inp)
inpx(i,:)=bitget(inp(i),8:-1:1);
end
l=length(inp);
x(1)=0.75;
mu=3.9;
for i=2:l
x(i)=mu*x(i-1)*(1-x(i-1));
end
x-min(x)
x=uint8(((x-min(x))/max(x))*255);
b=[];
for i=1:l
b(i,:)=bitget(x(i),8:-1:1);
end
temp=0;
outx=zeros(1,l);
for c=1:length(inp)
for i=1:8
for j=1:8
if (b(c,i)==0)&&(i==j)
weight(i,j)=1;
elseif (b(c,i)==1)&&(i==j)
weight(i,j)=-1;
elseif i~=j
weight(i,j)=0;
end
end
if(b(c,i)==0)
theta(i)=-1/2;
else theta(i)=1/2;
end
end
for i=1:8
dx(c,i)=hardlim(sum(weight(i,:).*inpx(c,:))+theta(i));
end
for i=1:8
outx(c)=outx(c)+uint8(dx(c,i))*(2^(8-i));
end
end
outx
