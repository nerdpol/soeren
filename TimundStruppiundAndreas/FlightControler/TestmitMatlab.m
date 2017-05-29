%Testroutine
i=instrfind;
if ~isempty(i)
    fclose(i);
end

s = serial('COM3','BaudRate',112500);
fopen(s)
%fprintf(s,'*IDN?')
idn = fscanf(s);
pause(5);
for k=1:100
    idn = fscanf(s)
    pause(0.3);
end
% for k=1:100
%    fwrite(s,[36 99 randi(90,5,1)' 10]); 
%    pause(0.1)
% end

pause(1);
fclose(s)