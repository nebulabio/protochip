function [Sf] = autofilter(S)
%% Autofilter
b   = size(S);% number of data sampes
c   = b(2)/2;
Sf  = S;
%% Filtering Data
% Filter was designed qualitatively through trial and error. The signal was
% smoothed out ignoring unlikely high frequency noise.
Fc = 55; % 8.25 kHz cutoff frequency
Fs = 1000; % 96 kHz sampling frequency
N  = 2;  % FIR filter order
LP = fdesign.lowpass('N,Fc',N,Fc,Fs); % Fs is always trailing argument
Hd = design(LP,'butter');
% fvtool(Hd)
for i = 1:c
    e          = (i*2);
    Sf(:,e) = filter(Hd,Sf(:,e));
end
end