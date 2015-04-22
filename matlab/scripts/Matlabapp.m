%% Matlabapp
% Code to analyze data from the cheapstat
%% UI
settings = Biochipui();%ui Prompt
%% Import
S        = importdata('ttry.tsv');%imports tests Data
Setsize  = str2num(settings{1});%Getting out Setsize
%% Plot raw data
if settings{2} == 'Y'
    autoplot(Setsize,S,'mV','nA','Raw Data') %Plotting Raw data
end
%% Filter and Plot Filtered Data
if settings{3} == 'Y'
    Sf       = autofilter(S);
    autoplot(Setsize,Sf,'mV','nA','Raw Data') %Plotting Filtered data
end
%% Autostats
[rsq] = autostats(Setsize,Sf)

