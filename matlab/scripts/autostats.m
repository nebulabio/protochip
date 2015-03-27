function [rrsq] = autostats(Setsize,S)
%% Autostats takes data coming from the cheapstat and runs reliability stats
% 
% Regression Analysis is done to gauge the difference between the data
% samples in one set. The minimum r-squared value for each set is output
%
% An Anova test is done to test if there is any significant difference
% between data from the same set. If the test were two be reliable there
% should be no difference.
%
% Set = defined as the data coming from the same
% voltametric test run on the same sample of solution. 
%
% Setnumber = Number Identifying which set the test is running in
%
% Array number = Test within the set that is being run against others
%% Seperate Time data
% Seperates time data out from the data to make cvalculations easier
[~,w] = size(S);
ls    = w/2;
for i = 1: ls;
    Ss(:,i) = S(:,(i*2));
end
%% Minimum R-Squared Value
% Each test is run against every other test in the set.
x  = 1; % Sets the first indexing values for rsq array
y  = Setsize-1;% """"
clear('rsq')
f = 0;% Sets the first setnumber offset value.
for c = 1:(ls/Setsize) % Setnumber
    clear('rsq')
    for e = 1:(Setsize-1)% Arraynumber changing
    clear('rsqs')
    for i = 1:(Setsize-e)
        v       = e-1;% Arraynumber
        rsqs(i) = Linearfit(Ss(:,((Setsize-v)+f)),Ss(:,(i+f)));
    end
    rsq(x:y) = rsqs;
    d        = Setsize - e;
    [~,x2]  = size(rsq);
    x        = x2+1;% Setting next index values for rsq array
    y        = x+d-2;% """"
    end
f  = (Setsize*c);% Setting the next Setnumber offset value
x  = 1;% Resetting next index values for rsq array
y  = Setsize-1;%""""
rsq = min(rsq);
rrsq(c) = rsq;% Outputting minimum r squared value
end
end

