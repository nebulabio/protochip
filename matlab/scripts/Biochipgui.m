function [Settings] = Biochipgui()
%Checkbox Gui for biochip data
prompt = {'SetSize','Plot Raw?:[Y/N]','Plot Filtered?[Y/N]',...
    'Run Stats?[Y/N]'};
dlg_title = 'Settings';
num_lines = 1;
def = {'2','Y','Y','Y'};
Settings = inputdlg(prompt,dlg_title,num_lines,def,'on');
end

