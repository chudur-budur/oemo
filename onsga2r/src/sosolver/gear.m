function f = gear(x)
%   The beam design problem

x_ = round(x) ; 
f1 = abs(6.931 - ((x_(3)/x_(1)) * (x_(4)/x_(2))));
f2 = max(x_) ;
f = [f1, f2];
end