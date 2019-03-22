function theta = invkine(L1,L2,px,py)
%theta = zeros(1,2);
r = sqrt(px^2+py^2);
beta = acos((L1^2+L2^2-px^2-py^2)/(2*L1*L2));
alpha = acos((px^2+py^2+L1^2-L2^2)/(2*L1*r));
gamma = atan2(py,px);
theta(1) = round((gamma - alpha),4);
theta(2) = round((pi-beta),4);
end
