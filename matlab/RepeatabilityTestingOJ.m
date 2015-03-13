%% Repeatability Testing orange Juice

% The experiment run is a sample of diluted orange juice was placed through
% the biochip. The cheapstat was run three seperate occasions using cyclic
% voltammetry creating 3 sets of data. The orange juice was then 
% concentrated and the experiment repeated. The more concentrated orange 
% juice are try4,5,&6. 

%% Collection
s          = whos('t*');
structSize = size(s);
ss         = structSize(1);
j          = 'ttry'

%% Close other figures
close all

% Autoplotter
for i = 1:structSize(:,1);
    c = ['try' (num2str(i)) '(:,1)'];
    d = {'try' (num2str(i)) '(:,2)'};
    plot(c,d)
    hold on
end
    
% Plotting the raw data.
plot(try1(:,1),try1(:,2))
hold on
plot(try2(:,1),try2(:,2))
plot(try3(:,1),try3(:,2))
plot(try6(:,1),try6(:,2),'g')
plot(try4(:,1),try4(:,2),'g')
plot(try5(:,1),try5(:,2),'g')
xlabel('mV');ylabel('nA');title('Raw Data')
legend('Original','','','Concentrated','','','Location','Northwest')


%% Spectral Analysis of Data
% Converted the units to Volts to make filtering easier
try1V = try1(:,1)./1000;
L    = length(try1(:,2));
Fs   = (1000);
NFFT = 2^nextpow2(L); % Next power of 2 from length of y
Y    = fft(try1(:,2),NFFT)/L; % Apply Fourier Transform
f    = Fs/2*linspace(0,1,NFFT/2+1);% Create Hz vector

% Plot single-sided amplitude spectrum.
figure(2)
plot(f,2*abs(Y(1:NFFT/2+1))) 
title('Single-Sided Amplitude Spectrum of y(t)')
xlabel('Frequency (Hz)')
ylabel('|Y(f)|')
axis([0 100 0 25])

% Some noise higher than the very low frequency actual data. To account
% there must be a low pass filter.

%% Filtering Data
% Filter was designed qualitatively through trial and error. The signal was
% smoothed out ignoring unlikely high frequency noise.
Fc = 55; % 8.25 kHz cutoff frequency
Fs = 1000; % 96 kHz sampling frequency
N  = 2;  % FIR filter order
LP = fdesign.lowpass('N,Fc',N,Fc,Fs); % Fs is always trailing argument
Hd = design(LP,'butter');
% fvtool(Hd)
y1 = filter(Hd,try1(:,2));
y2 = filter(Hd,try2(:,2));
y3 = filter(Hd,try3(:,2));
y4 = filter(Hd,try4(:,2));
y5 = filter(Hd,try5(:,2));
y6 = filter(Hd,try6(:,2));
% figure(1)
% plot(try1V,y,'g')

%% Linear Regression
[ p1,rsq1,PLAfit1 ] = Linearfit(try1(:,2),try2(:,2));
[ p2,rsq2,PLAfit2 ] = Linearfit(try1(:,2),try3(:,2));
[ p3,rsq3,PLAfit3 ] = Linearfit(try2(:,2),try3(:,2));
rsq0                = [rsq1 rsq2 rsq3];
msgbox(num2str(rsq0),'Raw 1st set');
[ p4,rsq4,PLAfit4 ] = Linearfit(y1,y2);
[ p5,rsq5,PLAfit5 ] = Linearfit(y1,y3);
[ p6,rsq6,PLAfit6 ] = Linearfit(y2,y3);
rsq00               = [rsq4 rsq5 rsq6];
msgbox(num2str(rsq00),'Filtered 1st set');









