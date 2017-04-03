function varargout = GUI_Control(varargin)
% GUI_CONTROL MATLAB code for GUI_Control.fig
%      GUI_CONTROL, by itself, creates a new GUI_CONTROL or raises the existing
%      singleton*.
%
%      H = GUI_CONTROL returns the handle to a new GUI_CONTROL or the handle to
%      the existing singleton*.
%
%      GUI_CONTROL('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in GUI_CONTROL.M with the given input arguments.
%
%      GUI_CONTROL('Property','Value',...) creates a new GUI_CONTROL or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before GUI_Control_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to GUI_Control_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help GUI_Control

% Last Modified by GUIDE v2.5 20-Mar-2017 21:11:31

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @GUI_Control_OpeningFcn, ...
                   'gui_OutputFcn',  @GUI_Control_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before GUI_Control is made visible.
function GUI_Control_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to GUI_Control (see VARARGIN)

i=instrfind;
if ~isempty(i)
    fclose(i);
end
handles.s = serial('COM8','BaudRate',112500);
fopen(handles.s)
% Choose default command line output for GUI_Control
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes GUI_Control wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = GUI_Control_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on slider movement.
function slider1_Callback(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
    channel(1)=floor(get(handles.slider1, 'Value'));
    channel(2)=floor(get(handles.slider2, 'Value'));
    channel(3)=floor(get(handles.slider3, 'Value'));
    channel(4)=floor(get(handles.slider4, 'Value'));
    channel(5)=floor(get(handles.slider5, 'Value'));
    send=[36 99 channel(1) channel(2) channel(3) channel(4) channel(5) 10]
    fwrite(handles.s,send); 

    handles=guidata(hObject);
    guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function slider1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider2_Callback(hObject, eventdata, handles)
% hObject    handle to slider2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
    channel(1)=floor(get(handles.slider1, 'Value'));
    channel(2)=floor(get(handles.slider2, 'Value'));
    channel(3)=floor(get(handles.slider3, 'Value'));
    channel(4)=floor(get(handles.slider4, 'Value'));
    channel(5)=floor(get(handles.slider5, 'Value'));
    send=[36 99 channel(1) channel(2) channel(3) channel(4) channel(5) 10]
    fwrite(handles.s,send); 

    handles=guidata(hObject);
    guidata(hObject, handles);
% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider3_Callback(hObject, eventdata, handles)
% hObject    handle to slider3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
    channel(1)=floor(get(handles.slider1, 'Value'));
    channel(2)=floor(get(handles.slider2, 'Value'));
    channel(3)=floor(get(handles.slider3, 'Value'));
    channel(4)=floor(get(handles.slider4, 'Value'));
    channel(5)=floor(get(handles.slider5, 'Value'));
    send=[36 99 channel(1) channel(2) channel(3) channel(4) channel(5) 10]
    fwrite(handles.s,send); 

    handles=guidata(hObject);
    guidata(hObject, handles);
% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider4_Callback(hObject, eventdata, handles)
% hObject    handle to slider4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
    channel(1)=floor(get(handles.slider1, 'Value'));
    channel(2)=floor(get(handles.slider2, 'Value'));
    channel(3)=floor(get(handles.slider3, 'Value'));
    channel(4)=floor(get(handles.slider4, 'Value'));
    channel(5)=floor(get(handles.slider5, 'Value'));
    send=[36 99 channel(1) channel(2) channel(3) channel(4) channel(5) 10]
    fwrite(handles.s,send); 

    handles=guidata(hObject);
    guidata(hObject, handles);
% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider5_Callback(hObject, eventdata, handles)
% hObject    handle to slider5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
    channel(1)=floor(get(handles.slider1, 'Value'));
    channel(2)=floor(get(handles.slider2, 'Value'));
    channel(3)=floor(get(handles.slider3, 'Value'));
    channel(4)=floor(get(handles.slider4, 'Value'));
    channel(5)=floor(get(handles.slider5, 'Value'));
    send=[36 99 channel(1) channel(2) channel(3) channel(4) channel(5) 10]
    fwrite(handles.s,send); 

    handles=guidata(hObject);
    guidata(hObject, handles);
% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
