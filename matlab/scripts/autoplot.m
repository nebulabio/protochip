function [ ] = autoplot(Setsize,S)
%% Collection
b   = size(S);% number of data sampes
c   = b(2)/2;
d   = c/Setsize;% # of sets
col = jet(d);% creates different colors # of sets
%% Plots all data and retrives handles
for i    = 1:c
    figure(1)
    h(i) = plot(S(:,i),S(:,i+1));
    hold on
end
%% Using handles changes colors based on sets
for i = 1:d
    e = i-1;
    for v  = 1:Setsize 
        ax = handle(h((e*Setsize)+v));
        ax.Color = col(i,:);
    end
end
%% Labels
xlabel('mV');ylabel('nA');title('Raw Data')
legend('Original','','','Concentrated','','','Location','Northwest')
end