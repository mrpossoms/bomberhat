function [ h, m, s ] = timeconv( seconds )
%TIMECONV From seconds, convert to hours, minutes and seconds.
h = floor(seconds/3600);
m_rem = rem(seconds, 3600);
m = floor(m_rem/60);
s = rem(m_rem, 60);
end

