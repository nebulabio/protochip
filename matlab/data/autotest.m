%% autostest
[l,w] = size(S);
ls    = w/2;
for i = 1: ls;
    Ss(:,i) = S(:,(i*2));
end
x  = 1;
y  = Setsize-1;
clear('rsq')
for e = 1:(Setsize-1)
    clear('rsqs')
    for i = 1:(Setsize-e)
        v      = e-1
        rsqs(i) = Linearfit(Ss(:,(Setsize-v)),Ss(:,i))
    end
    rsq(x:y) = rsqs
    d        = Setsize - e
    [xl,x2]  = size(rsq)
    x        = x2+1
    y        = x+d-2
end
rsq = min(rsq)