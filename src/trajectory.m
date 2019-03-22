function [yy t_sp]= trajectory(q,q_deg,t)
x = t; 
v1 = -10; %v1 and v2 define the slope of the trajectory at the beggining and ending point of the trajectory
v2 = 10;

y = [v1 q_deg(1,:) v1; 
     v2 q_deg(2,:) v2];
 
t_sp = linspace(0,t(end),100);

pp = spline(x,y);
yy = ppval(pp, t_sp);
end