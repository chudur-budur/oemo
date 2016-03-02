function[y] = array_factor(x, phi, phi_desired, distance, dim)
% As the function name signifies here the array factor is calculated 
 
pi = 3.141592654; 

% y1 = 0 ; y2 = 0 ;
% for i1 = 1:dim
%     delphi = 2 * pi * (i1-1)/dim;
%     shi = cos(phi - delphi) - cos(phi_desired * (pi/180) - delphi);
%     shi = shi * dim * distance;
%     if i1 <= dim/2
%         y1 = y1 + x(i1) * cos(shi + x(dim/2+i1) * (pi/180));
%         y2 = y2 + x(i1) * sin(shi + x(dim/2+i1) * (pi/180));
%     else
%         y1 = y1 + x(i1 - dim/2) * cos(shi - x(i1) * (pi/180));
%         y2 = y2 + x(i1 - dim/2) * sin(shi - x(i1) * (pi/180));
%     end;
% end;
% y = sqrt((y1 * y1) + (y2 * y2));

% vectorized version, little bit faster
y1 = zeros(1,dim); y2 = zeros(1,dim);
delphi = (2.0 * pi) .* ((0:1:dim-1) ./ dim);
shi_ = cos(phi - delphi) - cos((phi_desired * (pi/180)) - delphi);
shi = shi_ .* (dim * distance);
y1(1:dim/2) = x(1:dim/2) .* ...
                    cos(shi(1:dim/2) + (x(dim/2+1:dim) * (pi/180)));
y2(1:dim/2) = x(1:dim/2) .* ...
                    sin(shi(1:dim/2) + (x(dim/2+1:dim) * (pi/180)));
y1(dim/2+1:dim) = x(1:dim/2) .* ...
                cos(shi(dim/2+1:dim) - (x(dim/2+1:dim) * (pi/180)));
y2(dim/2+1:dim) = x(1:dim/2) .* ...
                sin(shi(dim/2+1:dim) - (x(dim/2+1:dim) * (pi/180)));
y1sum = sum(y1); y2sum = sum(y2);
y = sqrt((y1sum * y1sum) + (y2sum * y2sum));

end
