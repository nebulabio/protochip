%% Autoplot
%% Collection
a          = whos('t*');% Defining # of imported Variables
b          = size(a);
c          = b(1);
setsize    = 3;
d          = c/setsize;% # of sets
for i = 1:c
    figure(1)
    h(i) = plot(eval(['ttry',num2str(i),'(:,1)']),eval(['ttry',num2str(i),'(:,2)']));
    hold on
end
for i = 1:d
ax = handle(h(1))
ax.Color = 'Red'
xlabel('mV');ylabel('nA');title('Raw Data')
legend('Original','','','Concentrated','','','Location','Northwest')