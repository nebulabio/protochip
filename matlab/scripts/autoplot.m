function [] = autoplot(Setsize,S,xaxis,yaxis,name)
%% Autoplot autmoatically plots samples collected
% Plots are then color coded by set size
b   = size(S);% number of data sampes
c   = b(2)/2;
d   = c/Setsize;% # of sets
col = jet(d);% creates different colors # of sets
%% Plots all data and retrives handles
figure
for i     = 1:c
    % Column plot indexing
    colm1 = (i*2)-1;
    colm2 = (i*2);
    h(i)  = plot(S(:,colm1),S(:,colm2));
    hold on
end
%% Using handles to change colors based on sets
for i = 1:d
    e = i-1;
    for v  = 1:Setsize 
        ax = handle(h((e*Setsize)+v));
        ax.Color = col(i,:);
    end
end
%% Label
xlabel(xaxis);ylabel(yaxis);title(name)
%% Legend
% Finds all plotted lines, selects the first in each set based on stepsize
ah = get(gca,'Children');% find all line handles 
for i = 1:d
legndstr(i) = {strcat('set',num2str(i))};% creates cell array of names
v(i)        = [ah((i*Setsize)-1)];% creates array of line handles by setsize
end
legend(fliplr(v),legndstr,'Location','Northwest')% creates legend
end