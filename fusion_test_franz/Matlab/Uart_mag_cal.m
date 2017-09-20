
x=instrfind;
if ~isempty(x)
    fclose(x);
end



s = serial('/dev/ttyUSB1', 'BaudRate', 115200);
fopen(s);
cnt=1;


while(1)
    
    if (s.BytesAvailable)
        str=fscanf(s)
        ret= strsplit(str)
        if strcmp(ret{1},'mx')
            res(cnt,1:3)=[str2num(ret{3}),str2num(ret{6}),str2num(ret{9})];
            cnt=cnt+1;
        end
        
        
    end
    if cnt>1000
        break;
    end
end

fclose(s);
figure
plot(res(:,1),res(:,2),'ro')
xlabel 'x'
ylabel 'y'
figure
plot(res(:,2),res(:,3),'ro')
xlabel 'y'
ylabel 'z'
