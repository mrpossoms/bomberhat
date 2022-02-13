function verify_ortho( R1, R2, R3 )
%VERIFY_ORTHO Verifies orthogonality of three vectors. Errors otherwise.

if simeq(norm(R1), 1) == false || simeq(norm(R2), 1) == false || simeq(norm(R3), 1) == false
    error('[ERROR] Not all unit magnitude: {%2.8f %2.8f %2.8f}', norm(R1), norm(R2), norm(R3) ~= 1)
end
if ~simeq(cross(R1, R2), R3)
    error('[ERROR] r_1 x r_2 = [ %s] != [ %s]\n', sprintf('%d ', cross(R1, R2)), sprintf('%d ', R3))
end
if ~simeq(cross(R3, R1), R2)
    error('[ERROR] r_3 x r_1 = [ %s] != [ %s]\n', sprintf('%d ', cross(R1, R3)), sprintf('%d ', R2))
end

end

