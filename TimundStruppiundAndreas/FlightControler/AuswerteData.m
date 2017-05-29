%AuswerteScript

i=instrfind;
if ~isempty(i)
    fclose(i);
end
handles.s = serial('COM7','BaudRate',112500);
fopen(handles.s)



while(1)
    fread(handles.s)
end