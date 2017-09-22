cc
close all
x=instrfind;
if ~isempty(x)
    fclose(x);
end
fileID = fopen('log.txt','w');



s = serial('/dev/ttyUSB0', 'BaudRate', 115200);
fopen(s);
cnt=1;
figure(1)
pause(0.1)

while(1)
    
    if (s.BytesAvailable)
        str=fscanf(s);
        fprintf(fileID,str);
        ret= strsplit(str);
        if strcmp(ret{1},'mx')
            res(cnt,1:3)=[str2num(ret{3}),str2num(ret{6}),str2num(ret{9})];
        figure(1)
            plot(res(cnt,1),res(cnt,2),'ro')
            hold on
             plot(res(cnt,2),res(cnt,3),'bo')
             plot(res(cnt,3),res(cnt,1),'ko')
                 cnt=cnt+1;
        end
        disp(str);
            if cnt>1000
                break;
            end

    end
end
while(1)
    
    if (s.BytesAvailable)
        str=fscanf(s);
        fprintf(fileID,str);
        disp(str(1:end-1));

    end
end

fclose(fileID);
fclose(s);
figure
plot(res(:,1),res(:,2),'ro')
xlabel 'x'
ylabel 'y'
figure
plot(res(:,2),res(:,3),'ro')
xlabel 'y'
ylabel 'z'


figure
plot3(res(:,1),res(:,2),res(:,3),'ro')

xmagcor=(max(res(:,1))+min(res(:,1)))/2
ymagcor=(max(res(:,2))+min(res(:,2)))/2
zmagcor=(max(res(:,3))+min(res(:,3)))/2

figure
plot3(res(:,1)-xmagcor,res(:,2)-ymagcor,res(:,3)-zmagcor,'ro')

figure
plot(res(:,1),res(:,2),'ro')
hold on
plot(res(:,2),res(:,3),'bo')
plot(res(:,3),res(:,1),'ko')

figure
plot(res(:,1)-xmagcor,res(:,2)-ymagcor,'ro')
hold on
plot(res(:,2)-ymagcor,res(:,3)-zmagcor,'bo')
plot(res(:,3)-zmagcor,res(:,1)-xmagcor,'ko')

mres=1.5;

figure
plot((res(:,1)-xmagcor)*mres,(res(:,2)-ymagcor)*mres,'ro')
hold on
plot((res(:,2)-ymagcor)*mres,(res(:,3)-zmagcor)*mres,'bo')
plot((res(:,3)-zmagcor)*mres,(res(:,1)-xmagcor)*mres,'ko')
