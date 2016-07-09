function [] = GUI_8()
% Demonstrate how to tell which button in a uibuttongroup is selected.  
% Similar to GUI_6 except that a uibuttongroup which enforces exclusivity 
% is used.
%
% Suggested exercise:  Make the editbox change the selected radiobutton.
% Be sure to check that user input is valid.  
%
%
% Author:  Matt Fig
% Date:  7/15/2009

S.fh = figure('units','pixels',...
              'position',[300 300 250 200],...
              'menubar','none',...
              'name','GUI_8',...
              'numbertitle','off',...
              'resize','off');
S.bg = uibuttongroup('units','pix',...
                     'pos',[20 100 210 90]);
S.rd(1) = uicontrol(S.bg,...
                    'style','rad',...
                    'unit','pix',...
                    'position',[20 50 70 30],...
                    'string','Radio 1');
S.rd(2) = uicontrol(S.bg,...
                    'style','rad',...
                    'unit','pix',...
                    'position',[20 10 70 30],...
                    'string','Radio 2');
S.rd(3) = uicontrol(S.bg,...
                    'style','rad',...
                    'unit','pix',...
                    'position',[120 50 70 30],...
                    'string','Radio 3');
S.rd(4) = uicontrol(S.bg,...
                    'style','rad',...
                    'unit','pix',...
                    'position',[120 10 70 30],...
                    'string','Radio 4');                
S.ed = uicontrol('style','edit',...
                 'unit','pix',...
                 'position',[100 60 50 30],...
                 'string','1');                
S.pb = uicontrol('style','push',...
                 'unit','pix',...
                 'position',[75 20 100 30],...
                 'string','Get Current Radio',...
                 'callback',{@pb_call,S});
            
             
function [] = pb_call(varargin)
% Callback for pushbutton.
S = varargin{3};  % Get the structure.

% Instead of switch, we could use num2str on:   
% find(get(S.bg,'selectedobject')==S.rd)      (or similar)
% Note the use of findobj.  This is because of a BUG in MATLAB, whereby if
% the user selects the same button twice, the selectedobject property will
% not work correctly.
switch findobj(get(S.bg,'selectedobject'))
    case S.rd(1)
        set(S.ed,'string','1') % Set the editbox string.
    case S.rd(2)
        set(S.ed,'string','2')
    case S.rd(3)
        set(S.ed,'string','3')
    case S.rd(4)
        set(S.ed,'string','4')
    otherwise
        set(S.ed,'string','None!') % Very unlikely I think.
end