clear, close all, clc
%Leg length
L1 = 100e-3;
L2 = 205e-3;

filename = 'export.xlsx';
sheet = 1;
%xlRange = 'P:Q';
%desired_position = xlsread(filename,sheet,xlRange);  %Takes data of desired leg desired_position (x,y) from excel document
x2Range = 'N:O';
desired_position_total = xlsread(filename,sheet,x2Range);
x3Range = 'V:W';
desired_position = xlsread(filename,sheet,x3Range);

%t = xlsread(filename,sheet,'R:R');     %For using 11 data points
%t = xlsread(filename,sheet,'M:M');      %For using the total of data points
t = xlsread(filename,sheet,'X:X');      %For using 7 data points

figure
hold on
for i = 1:length(desired_position)
%for i = 1:5
    px = desired_position(i,1)*1e-03;
    py = desired_position(i,2)*1e-03;
    q(:,i) = invkine(L1,L2,px,py);
    
    L1x = L1*cos(q(1,i));
    L1y = L1*sin(q(1,i));
    x(i) = L1x + L2*cos(q(1,i)+q(2,i));
    y(i) = L1y + L2*sin(q(1,i)+q(2,i));

    line([0 L1x],[0 L1y],'Color','blue')
    line([L1x x(i)],[L1y y(i)],'Color','red')
    plot(0,0,'b*')
    plot(L1x,L1y,'r*')
    plot(x(i),y(i),x(i),y(i),'m*')
    title('Inverse kinematics for leg desired position (x,y)')
    xlabel('x desired position')
    ylabel('y desired position')
end
hold off

q_deg = rad2deg(q)  %Get angles in degrees

[q_deg_sp t_sp]= trajectory(q,q_deg,t);

figure
hold on
plot(q_deg(1,:),q_deg(2,:),q_deg(1,:),q_deg(2,:),'o')
plot(q_deg_sp(1,:),q_deg_sp(2,:),'-r',q_deg(1,:),q_deg(2,:),'or')
title('\theta_1 vs \theta_2')';
legend('Original data points','','Cubic spline approximation')

figure
hold on
plot(t,q_deg(1,:),t,q_deg(1,:),'o')
title('\theta_1 vs t');
plot(t_sp,q_deg_sp(1,:),'-r')
legend('Original data points','','Cubic spline approximation')

figure
hold on
plot(t,q_deg(2,:),t,q_deg(2,:),'o')
title('\theta_2 vs t');
plot(t_sp,q_deg_sp(2,:),'-r')
legend('Original data points','','Cubic spline approximation')