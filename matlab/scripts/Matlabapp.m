%% Matlabapp
settings = Biochipgui();%Gui Prompt
S        = importdata('ttry.tsv');%imports tests Data
Setsize  = str2num(settings{1});%Getting out Setsize
autoplot(Setsize,S) %Plotting Raw data


