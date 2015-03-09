%% Protochip Testing Code
% Find a serial port object.
obj1 = instrfind('Type', 'serial', 'Port', 'COM5', 'Tag', '');

% Create the serial port object if it does not exist
% otherwise use the object that was found.
if isempty(obj1)
    obj1 = serial('COM5');
else
    fclose(obj1);
    obj1 = obj1(1)
end

% Flush the data in the input buffer.
% flushinput(obj1);
fopen(obj1)
out = fread(obj1,64,'int16','l',)