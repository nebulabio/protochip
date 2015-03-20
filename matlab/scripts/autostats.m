function [rsq] = autostats(Setsize,S)
ls = size(S);
ls = ls(2)/2;
for i = 1: ls
    Ss(:,i) = S(:,(i*2));
end
for i = 1:(Setsize-1)
    rsq(i) = Linearfit(Ss(:,Setsize),Ss(:,i));
end

