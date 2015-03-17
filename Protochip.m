%% Protochip Testing Code
% Find a serial port object.
obj1 = instrfind('Type', 'serial', 'Port', 'COM5', 'Tag', '');

% Create the serial port object if it does not exist
% otherwise use the object that was found.
if isempty(obj1)
    obj1 = serial('COM5');
else
    fclose(obj1);
    obj1 = obj1(1);
end

%Flush the data in the input buffer.
flushinput(obj1);
fopen(obj1)
set(obj1,'Terminator','CR')
A = fscanf(obj1,'%s')
% B = fread(obj1,'uint8')
% d = 736034.599826;
% fgets(obj1)
% A = fscanf(obj1,'%x')
% 
% fid = fopen(fullfile(pathname, filenameAll));
% fopen(obj1)
% [a,b] = hexfread(obj1,6)
% str = native2unicode(fread(obj1))
% A = sscanf(str,'%x %x')
% format hex
% [mformat] = fopen(obj1);
% fclose(obj1)
% set(obj1,'Terminator','CR')
% [A,count,msg]  = fread(obj1,64,'short')
% [b,count,msg]  = fread(obj1,64,'short')
% out1  = fread(obj1,512/16,'int16')
% out2  = fread(obj1,512/16,'int16')
% out4  = fread(obj1,512/16,'int16')
% out5  = fread(obj1,512/16,'int16')
% out6  = fread(obj1,512/16,'int16')
% out7  = fread(obj1,512/16,'int16')
% out8  = fread(obj1,512/16,'int16')
% out9  = fread(obj1,512/16,'int16')
% out10 = fread(obj1,512/16,'int16')
% out11 = fread(obj1,512/16,'int16')
% out12 = fread(obj1,512/16,'int16')
% out13 = fread(obj1,512/16,'int16')
% out14 = fread(obj1,512/16,'int16')
% out15 = fread(obj1,512/16,'int16')
% out16 = fread(obj1,512/16,'int16')

s = serial('COM5');
s.BaudRate = 9600
fopen(s)
fscanf(s,'%X')