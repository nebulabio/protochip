hrealterm=actxserver('realterm.realtermintf'); % start Realterm as a server
% Only use these 3 lines to see what properties and methods realterm has.....
fprintf(1,'\nProperties of Realterm\n\n');
get(hrealterm) %List all properties.
try
set(hrealterm) %In later versions of matlab, this will show you what possible values the enumerations can take
catch
end
fprintf(1,'\n\nMethods of Realterm\n\n');
invoke(hrealterm) %List all functions
% some example properties
hrealterm.baud=9600;
hrealterm.caption='Matlab Realterm Server';
hrealterm.windowstate=1; %minimized
hrealterm.PortOpen=5; %open the comm port
is_open=(hrealterm.PortOpen~=1); %check that it opened OK
hrealterm.displayas=2; %show hex in terminal window
hrealterm.CaptureFile='c:\temp\matlab_data.dat'
invoke(hrealterm,'startcapture'); %start capture
%do what you want here
fprintf(1,'\n\nTry what you want here. Type RETURN to end demo and close realterm\n')
keyboard
invoke(hrealterm,'stopcapture');
try %try to close any we can in case they are faulty.
invoke(hrealterm,'close'); delete(hrealterm);
catch
fprintf('unable to close realterm')
end; %try