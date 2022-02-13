function [ ok ] = simeq( value, exp )
%SIMEQ A simple float test at 1e-6.

for i=1:length(value)
    if abs(value(i) - exp(i)) >= 1e-6
        ok = false;
        return
    end
end
ok = true;

end

